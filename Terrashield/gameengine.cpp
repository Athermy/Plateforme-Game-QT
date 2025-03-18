#include "gameengine.h"
#include "collidemanager.h"
#include "configuration.h"
#include "enemy.h"
#include "fixedblock.h"
#include "mobileenemy.h"
#include "player.h"
#include "unit.h"


GameEngine::GameEngine()
{
    //inicializar tamanho de janela
    windowWidth = WINDOW_WIDTH;
    windowHeight = WINDOW_HEIGHT;

    //título e ícone
    setWindowTitle(TITLE);
    setWindowIcon(QIcon(":/resources/images/icone.ico"));

    //criando a scene
    levelScene = new QGraphicsScene();

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //plano do jogo
    worldPlan = new QGraphicsItemGroup();
    levelScene->addItem(worldPlan);

    //inicializar mapa
    map = new Map();

    map->generateMap2();
    map->saveMap(map->getName());
    map->clearMap();
    map->generateMap1();
    map->saveMap(map->getName());
    map->clearMap();
    map->generateMap3();
    map->saveMap(map->getName());
    map->clearMap();

    //inicializar timers
    refreshTimer = new QTimer(this);
    connect(refreshTimer,SIGNAL(timeout()),this,SLOT(updateAllPositions()));

    Animtimer = new QTimer(this);
    connect(Animtimer,SIGNAL(timeout()),this,SLOT(animate()));

    restartTimer = new QTimer();
    connect(restartTimer,SIGNAL(timeout()),this,SLOT(restart()));

    horizontalScrollBar()->setValue(0);
    verticalScrollBar()->setValue(0);
    horizontalScrollBar()->setPageStep(0);
    spacePressed = false;

    //inicializar número do sprite para a animação
    playerSprite = 1;
    playerStaticCounter = 1;

    // inicializa menu principal
    menuScene = new Menu();

    // Linka botões dos mapas no menu
    buttonMenuMapper = new QSignalMapper(this);
    foreach(MenuButton * btn ,menuScene->getButtonList()){
        buttonMenuMapper->setMapping(btn, btn->text());
        connect(btn,SIGNAL(clicked()),buttonMenuMapper,SLOT(map()));
    }
    connect(buttonMenuMapper, SIGNAL(mapped(QString)), this, SLOT(loadMap(QString)));
    // linka botão quit ao menu
    connect(menuScene->getQuitBtn(),SIGNAL(clicked()),this,SLOT(quitApp()));

    //inicializa menu de pause
    pauseMenu = new PauseGroup();
    connect(pauseMenu->getContinueBtn(), SIGNAL(clicked()), this, SLOT(closePause()));
    connect(pauseMenu->getBackMenuBtn(), SIGNAL(clicked()), this, SLOT(openMenu()));
    paused = false;

    // inicializa menu de vitória
    victoryMenu = new VictoryGroup();
    connect(victoryMenu->getRetryBtn(), SIGNAL(clicked()), this, SLOT(retryMap()));
    connect(victoryMenu->getBackMenuBtn(), SIGNAL(clicked()), this, SLOT(openMenu()));
    finished = false;

    openMenu();

    showFullScreen();

}

GameEngine::~GameEngine()
{
    qDebug() << "delete";
    Animtimer->stop();
    delete Animtimer;
    refreshTimer->stop();
    delete refreshTimer;

    delete buttonMenuMapper;

    delete map;

    delete menuScene;

    delete pauseMenu;

    levelScene->clear();
    delete levelScene;
}

void GameEngine::keyPressEvent(QKeyEvent *event)
{
    if(paused == false){

        if (event->key() == Qt::Key_Left){
            map->getPlayer()->SetMovingLeft(true);
        }
        else if (event->key() == Qt::Key_Right){
            map->getPlayer()->SetMovingRight(true);
        }
        else if (event->key() == Qt::Key_Up){
            if(!map->getPlayer()->isFlying())
            map->getPlayer()->jump();
        }

        else if (event->key() == Qt::Key_R){ //retry
            loadMap(map->getName());
        }
    }
    //abre ou fecha menu de pause
    if (event->key() == Qt::Key_Escape){
        if(scene() == levelScene && finished == false){
            if(pauseMenu->scene() == levelScene)
                closePause();
            else
                openPause();
        }
    }
    //muda entre fullscreen e modo janela
    if (event->key() == Qt::Key_F11){
        if(isFullScreen())
            showNormal();
        else
            showFullScreen();
    }
}

void GameEngine::keyReleaseEvent(QKeyEvent *event)
{
    //qDebug() << "key released" ;
    if (event->key() == Qt::Key_Left){
        map->getPlayer()->SetMovingLeft(false);
    }
    else if (event->key() == Qt::Key_Right){
        map->getPlayer()->SetMovingRight(false);
    }
    else if (event->key() == Qt::Key_Space){
        if(event->isAutoRepeat())
            event->ignore();
        else
            spacePressed = false;
    }
}

void GameEngine::resizeEvent(QResizeEvent *event)
{
    qDebug() << "resize";
    if(levelScene)
        levelScene->setSceneRect(0,0,map->getWidth(),map->getHeight());
    //escala para o tamanho novo
    QRect rect = QRect(0,0,WINDOW_WIDTH,map->getHeight());
    fitInView(rect);
}

void GameEngine::updatePlayerPosition()
{
    map->getPlayer()->updateMovementStates();

    CollideManager<FixedBlock> * wallCollider = new CollideManager<FixedBlock>(map->getPlayer(),true,true,true,true);
    CollideManager<Enemy> * enemyCollider = new CollideManager<Enemy>(map->getPlayer(),true,false,false,false);
    CollideManager<Finish> * finishCollider = new CollideManager<Finish>(map->getPlayer(),false,false,false,false);

    int next_x = map->getPlayer()->x();
    int next_y = map->getPlayer()->y();

    //Movendo o jogador
    if(map->getPlayer()->isFlying() == true){
        next_y += map->getPlayer()->getYForce() * 1/FPS;
        float dt = 1/(float)FPS;
        map->getPlayer()->setYForce( map->getPlayer()->getYForce() + map->getPlayer()->getWeight() * GRAVITY * dt);
    }
    if(map->getPlayer()->isMovingLeft()){
        map->getPlayer()->increaseLeftForce();
    }
    else if(map->getPlayer()->isMovingRight()){
        map->getPlayer()->increaseRightForce();
    }
    else {
        map->getPlayer()->decreaseXForce();
    }
    next_x += map->getPlayer()->getXForce();
    map->getPlayer()->setPos(next_x,next_y);

    //verifica se está fora do mapa
    if(map->getPlayer()->x() < worldPlan->x() ||
        map->getPlayer()->x() + map->getPlayer()->getWidth() > map->getWidth() ||
        map->getPlayer()->y() > map->getHeight() - map->getPlayer()->getHeight()){
        gameOver();
    }

    wallCollider->updateCollidingPosition();
    enemyCollider->updateCollidingPosition();
    finishCollider->updateCollidingPosition();

    //se não tiver bloco ou inimigo para colidir, cai
    if(!wallCollider->getAreColliding() && !enemyCollider->getAreColliding()){
        if(map->getPlayer()->getYForce() == 0)
            map->getPlayer()->setYForce(map->getPlayer()->getYForce() + 100);
    }

    if(enemyCollider->getAreColliding()){
        QMap<Enemy *,fromPosition> enemyMap = enemyCollider->getCollidingItemList();
        QMapIterator<Enemy*, fromPosition> iterator(enemyMap);
        while (iterator.hasNext()) {
            iterator.next();
            Enemy * enemy = iterator.key();
            if(iterator.value().fromTop == true){
                //quicou
                map->getPlayer()->bounce();

                //matando inimigo
                map->getUnitList()->removeOne(enemy);
                worldPlan->removeFromGroup(enemy);
                delete iterator.key();
            }

            if(!map->getPlayer()->isAlive()){
                    gameOver();
                }
            }
        }


    //se tocar o painel de controle final
    if(finishCollider->getAreColliding()){

        victory();
    }


    delete wallCollider;
    delete enemyCollider;
    delete finishCollider;
}



void GameEngine::respawn()
{
    map->getPlayer()->setPos(200,400);
}

//segue o player
void GameEngine::updateCamera()
{
    //se player estiver muito para a esquerda
    if (map->getPlayer()->x() - CAMERA_LEFT > 0 && map->getPlayer()->x() + worldPlan->x() < CAMERA_LEFT ){
        worldPlan->setPos(-(map->getPlayer()->x() - CAMERA_LEFT),0);
    }
    //player no começo do mapa
    else if (map->getPlayer()->x() - CAMERA_LEFT < 0){
        worldPlan->setPos(0,0);
    }
    //se player estiver muito para a direita
    if (map->getPlayer()->x() + WINDOW_WIDTH - CAMERA_RIGHT < map->getWidth() && map->getPlayer()->x() + worldPlan->x() > CAMERA_RIGHT ){
        worldPlan->setPos(-(map->getPlayer()->x() - CAMERA_RIGHT) , 0);
    }
}

void GameEngine::updateAllPositions()
{
    updatePlayerPosition();
    updateEnemyPosition();
    updateMobileEnemyPosition();
    updateCamera();
}

void GameEngine::animate()
{
    //se player estiver imune
    if(map->getPlayer()->getImmune() && playerSprite % 3 == 0){
        map->getPlayer()->hide();
    }
    else{
        map->getPlayer()->show();
    }


    //se o player estiver no ar
    if(map->getPlayer()->isJumping()){
        if(playerSprite < 21 /*|| playerSprite > 26*/)
            playerSprite = 21;


        map->getPlayer()->setSprite(QString(":/resources/images/player/%21.png").arg(playerSprite));
        playerSprite ++;

        if(playerSprite > 26)
            playerSprite = 26;
    }
    else if (map->getPlayer()->isFalling()){
        if(playerSprite < 27 /*|| playerSprite > 30*/)
            playerSprite = 27;

        map->getPlayer()->setSprite(QString(":/resources/images/player/%27.png").arg(playerSprite));
        playerSprite ++;

        if(playerSprite > 30)
            playerSprite = 30;

    }
    //se player correr
    else if(map->getPlayer()->isMovingRight() || map->getPlayer()->isMovingLeft()){
        if(playerSprite < 11 || playerSprite > 18)
            playerSprite = 11;
        map->getPlayer()->setSprite(QString(":/resources/images/player/p%11.png").arg(playerSprite));
        playerSprite ++;
    }
    //se player está parado
    else if(map->getPlayer()->getFixed()){
        if(playerSprite > 9 || playerSprite < 1)
            playerSprite = 1;
        map->getPlayer()->setSprite(QString(":/resources/images/player/%1.png").arg(playerSprite));

        playerStaticCounter ++;
        playerSprite ++;
        //se player piscar, pula o primeiro sprite
        if(playerSprite == 5){
            playerSprite = 2;
        }
        //se player não piscar por um tempo, vai piscar
        else if(playerSprite > 3 && playerStaticCounter > 10){
            playerSprite = 4;
            playerStaticCounter = 1;
        }
        //player não pisca
        else if(playerSprite > 3 ){
            playerSprite = 1;
        }
    }

}


void GameEngine::retryMap()
{
    loadMap(map->getName());
}

void GameEngine::loadMap(QString worldName)
{

    if(finished == true){
        closeVictory();
    }

    worldPlan->setPos(0,0);
    clearLevel();
    map->readmap(worldName);
    drawElements();

    // Adapta o tamanho da janela ao mapa
    levelScene->setSceneRect(0,0,map->getWidth(),map->getHeight());
    QRect rect = QRect(0,0,WINDOW_WIDTH,map->getHeight());
    fitInView(rect);

    openGame();
}

void GameEngine::drawElements()
{
    levelScene->setBackgroundBrush(QImage(map->getBackground()));

    // player
    worldPlan->addToGroup(map->getPlayer());

    // seta elements
    for(Element * element : *map->getElementList()){
        worldPlan->addToGroup(element);
    }
    //seta inimigos
    for(Unit * unit : *map->getUnitList()){
        worldPlan->addToGroup(unit);
    }

}


void GameEngine::updateEnemyPosition()
{
    // for all mobile enemy
    for(Unit * enemy: *map->getUnitList()){
        if(enemy->getType() == "enemy"){
            Enemy * enemy1 = dynamic_cast<Enemy*>(enemy);

            CollideManager<FixedBlock> * wallCollider = new CollideManager<FixedBlock>(enemy,true,true,true,true);
            CollideManager<Enemy> * enemyCollider = new CollideManager<Enemy>(enemy,true,true,true,true);

            // calculate next mobile enemy position
            int next_y = enemy1->y();
            if (enemy1->isFlying() == true){
                next_y += enemy1->getYForce() * 1/FPS;
                float dt = 1/(float)FPS;
                enemy1->setYForce( enemy1->getYForce() + enemy1->getWeight() * GRAVITY * dt);
            }

            // update position and adapt position with collision
            enemy1->setPos(enemy1->getXForce() + enemy1->x(),next_y);

            // check if out of the map -> kill enemy if out of the map
            if(enemy1->x() < worldPlan->x() || enemy1->x() + enemy1->getWidth() > map->getWidth() ||
                enemy1->y() > map->getHeight() - enemy1->getHeight()){
                map->getUnitList()->removeOne(enemy1);
                delete enemy1;
                delete wallCollider;
                delete enemyCollider;
                return;
            }

            wallCollider->updateCollidingPosition();
            enemyCollider->updateCollidingPosition();

            // If no wall-> begin de falling
            if(!wallCollider->getAreColliding() || !enemyCollider->getAreColliding()){
                // if initial falling
                if(enemy1->getYForce() == 0)
                    enemy1->setYForce(100);
            }
            else{
                QMap<FixedBlock *,fromPosition> blocMap = wallCollider->getCollidingItemList();
                QMap<Enemy *,fromPosition> blocMap1 = enemyCollider->getCollidingItemList();
                QMapIterator<Enemy*, fromPosition> iterator1(blocMap1);
                QMapIterator<FixedBlock*, fromPosition> iterator(blocMap);

            }
            delete wallCollider;
            delete enemyCollider;
        }
    }
}

void GameEngine::updateMobileEnemyPosition()
{
    // for all mobile enemy
    for(Unit * enemy: *map->getUnitList()){
        if(enemy->getType() == "mobileEnemy"){
            MobileEnemy * mbEnemy = dynamic_cast<MobileEnemy*>(enemy);

            //qDebug() << mbEnemy->getXForce();

            CollideManager<FixedBlock> * wallCollider = new CollideManager<FixedBlock>(enemy,true,true,true,true);

            // calculate next mobile enemy position
            int next_y = mbEnemy->y();
            if (mbEnemy->isFlying() == true){
                next_y += mbEnemy->getYForce() * 1/FPS;
                float dt = 1/(float)FPS;
                mbEnemy->setYForce( mbEnemy->getYForce() + mbEnemy->getWeight() * GRAVITY * dt);
            }

            // update position and adapt position with collision
            mbEnemy->setPos(mbEnemy->getXForce() + mbEnemy->x(),next_y);

            // check if out of the map -> kill enemy if out of the map
            if(mbEnemy->x() < worldPlan->x() ||
                mbEnemy->x() + mbEnemy->getWidth() > map->getWidth() ||
                //map->getPlayer()->y() < worldPlan->y() ||
                mbEnemy->y() > map->getHeight() - mbEnemy->getHeight()){
                map->getUnitList()->removeOne(mbEnemy);
                delete mbEnemy;
                delete wallCollider;
                return;
            }

            wallCollider->updateCollidingPosition();

            // If no wall-> begin de falling
            if(!wallCollider->getAreColliding()){
                // if initial falling
                if(mbEnemy->getYForce() == 0)
                    mbEnemy->setYForce(100);
            }
            else{
                QMap<FixedBlock *,fromPosition> blocMap = wallCollider->getCollidingItemList();
                QMapIterator<FixedBlock*, fromPosition> iterator(blocMap);

                // if enemy touch a side of a block, it will go back
                while (iterator.hasNext()) {
                    iterator.next();
                    if((iterator.value().fromLeft || iterator.value().fromRight) &&
                        !iterator.value().fromUnder && !iterator.value().fromTop){
                        mbEnemy->switchSide();
                        break;
                    }
                }
            }
            delete wallCollider;
        }
    }
}

void GameEngine::openMenu()
{
    if(paused == true)
        closePause();

    paused = true;
    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    // stop timers
    Animtimer->stop();
    refreshTimer->stop();

    // replace scene by menu scene
    setScene(menuScene);

}

void GameEngine::quitApp()
{
    this->close();
}

void GameEngine::restart()
{
    restartTimer->stop();
    loadMap(map->getName());
}


void GameEngine::openGame()
{
    //esconde cursor do mouse
    QApplication::setOverrideCursor(Qt::BlankCursor);

    //inicia timer
    Animtimer->start(90);
    refreshTimer->start(1000/FPS);
    setScene(levelScene);
    paused = false;
}

void GameEngine::openPause()
{

    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    // stop timer
    paused = true;
    pauseTimer();

    levelScene->addItem(pauseMenu);
    levelScene->addWidget(pauseMenu->getContinueBtn());
    levelScene->addWidget(pauseMenu->getBackMenuBtn());
}

void GameEngine::closePause()
{

    //esconde novamente cursor do mouse
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // restarta timers
    paused = false;
    resumeTimer();

    // remove pause da cena
    levelScene->removeItem(pauseMenu);
    levelScene->removeItem(pauseMenu->getBackMenuBtn()->graphicsProxyWidget());
    levelScene->removeItem(pauseMenu->getContinueBtn()->graphicsProxyWidget());
    pauseMenu->getBackMenuBtn()->graphicsProxyWidget()->setWidget( NULL );
    pauseMenu->getContinueBtn()->graphicsProxyWidget()->setWidget( NULL );
}

void GameEngine::clearLevel()
{
    map->clearMap();
    worldPlan->setPos(0,0);
    if (restartTimer->isActive()){
        restartTimer->stop();
    }
}

void GameEngine::gameOver()
{
    map->getPlayer()->setSprite(":/resources/images/player/phurt.png");

    pauseTimer();


    restartTimer->start(1000);


}

void GameEngine::pauseTimer()
{
    Animtimer->stop();
    refreshTimer->stop();
    if (restartTimer->isActive() && paused == true){
        overRemainTime = restartTimer->remainingTime();
        restartTimer->stop();
    }
    else
        overRemainTime = 1000;


}

void GameEngine::resumeTimer()
{
    if(overRemainTime < 1000)
        restartTimer->start(overRemainTime);
    Animtimer->start(90);
    refreshTimer->start(1000/FPS);

}

void GameEngine::victory()
{
    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    pauseTimer();
    finished = true;
    levelScene->addItem(victoryMenu);
    levelScene->addWidget(victoryMenu->getRetryBtn());
    levelScene->addWidget(victoryMenu->getBackMenuBtn());
}

void GameEngine::closeVictory()
{
    // hide mouse cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);
    levelScene->removeItem(victoryMenu);
    finished = false;
    // remove victory component from scene
    levelScene->removeItem(victoryMenu->getBackMenuBtn()->graphicsProxyWidget());
    levelScene->removeItem(victoryMenu->getRetryBtn()->graphicsProxyWidget());
    // reset proxy
    victoryMenu->getBackMenuBtn()->graphicsProxyWidget()->setWidget( NULL );
    victoryMenu->getRetryBtn()->graphicsProxyWidget()->setWidget( NULL );
}

