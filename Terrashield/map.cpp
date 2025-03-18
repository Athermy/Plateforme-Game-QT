#include "map.h"
#include "wall.h"
#include "enemy.h"
#include "mobileenemy.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QDirIterator>


Map::Map()
{
    player = NULL;
    elementList = new QList<Element*>();
    unitList = new QList<Unit*>();
    name = "noName";
    difficulty = 0;
}

Map::~Map()
{
    clearMap();
    if(player)
        delete player;
    delete elementList;
    delete unitList;
}

void Map::generateMap1()
{
    width = 6400;
    height = 1280;
    difficulty = 0;

    //setando background
    backgroundPath = ":/resources/images/backgrounds/War2.png";
    setBackground(QImage(backgroundPath));


    //criando player
    player = new Player();
    player->setPos(200,700);

    name = "Starting Area";

    //criando mapa

    //chão
    for(int i = 0; i < 70; i++){

        Wall * bloc = new Wall();
        bloc->setPos(i*bloc->getWidth(),800);
        elementList->append(bloc);

        //inimigo estático no chão
        if(i == 12){
            Enemy * enemy = new Enemy();
            enemy->setPos(i*bloc->getWidth(), 800 - enemy->getHeight());
            unitList->append(enemy);

            for(int k=0; k<2;k++){
                Enemy * enemy1 = new Enemy();
                enemy1->setPos(i*bloc->getWidth() + enemy1->getWidth() + 50, 800 - (k+1) * enemy1->getHeight());
                unitList->append(enemy1);
            }
        }
        //paredinha para inimigo móvel
        if(i==25){
            Wall * bloc2 = new Wall();
            bloc2->setPos(i*bloc->getWidth(),800 - bloc2->getHeight());
            elementList->append(bloc2);
        }
        //inimigo móvel
        if(i==27 || i==32 || i==40 || i==50 || i==56){
            MobileEnemy * mb = new MobileEnemy();
            mb->setPos(i*bloc->getWidth(),800 - mb->getHeight());
            unitList->append(mb);
        }
        if(i == 19 || i==20 || i==21 || i==22){
            // hole
            elementList->removeOne(bloc);
            delete bloc;
        }
        //paredinha para inimigo móvel
        if(i==58){
            Wall * bloc3 = new Wall();
            bloc3->setPos(i*bloc->getWidth(),800 - bloc3->getHeight());
            elementList->append(bloc3);

        }
        //plataforma elevada
        for(int i = 58; i < 63; i++){
            Wall * bloc = new Wall();
            bloc->setPos(i*bloc->getWidth() + 100 ,600);
            elementList->append(bloc);
        }
        //inimigos na plataforma elevada
        if(i==60){
            for(int j = 0; j < 7; j++){
                Enemy * ene = new Enemy();
                ene->setPos(i*bloc->getWidth() + 100, 600 - (j+1) * ene->getHeight());
                unitList->append(ene);
            }
        }
        //buraco
        if(i>=58 && i<63){
            elementList->removeOne(bloc);
            i++;
            delete bloc;
        }

        if(i == 5){
            for(int j=0;j<5;j++){
                Wall * bloc = new Wall();
                bloc->setPos(i*bloc->getWidth(),600 - (j+1) * bloc->getHeight());
                elementList->append(bloc);
                if(j==4){
                    Enemy * ene = new Enemy();
                    ene->setPos(i*bloc->getWidth()-10, 600 - (j+2) * ene->getHeight());
                    unitList->append(ene);
                }
            }
        }
        if(i == 69){
            Finish *fim = new Finish();
            fim->setPos(i*bloc->getWidth(),800 - fim->getHeight());
            elementList->append(fim);
        }
    }
    //teto inicial
    for(int i = 0; i < 6; i++){
        Wall * bloc = new Wall();
        bloc->setPos(i*bloc->getWidth() + 200 ,600);
        elementList->append(bloc);
    }
    //parede inicial
    for(int i = 14; i >= 0; i--){
        Wall * bloc = new Wall();
        bloc->setPos(0 ,800 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);
        if(i==7){
            Wall * bloc = new Wall();
            bloc->setPos(bloc->getHeight(),800 - bloc->getHeight() - i * bloc->getHeight());
            elementList->append(bloc);
        }
    }
    //parede menor
    for(int i = 3; i >= 0; i--){
        Wall * bloc = new Wall();
        bloc->setPos(500 ,800 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);
    }
}

void Map::generateMap2()
{
    width = 700;
    height = 200;

    difficulty = 2;

    //background
    backgroundPath = ":/resources/images/backgrounds/War2.png";


    //cria player
    player = new Player();
    player->setPos(200,500);

    name = "Enemy Base";

    //Cria mapa

    //Chão
    for(int i = 0; i < 80; i++){
        if(i != 29 && i != 30 && i !=31){
            Wall * bloc = new Wall();
            bloc->setPos(i*bloc->getWidth(),800);
            elementList->append(bloc);
        }
        Wall * bloc = new Wall();

        if(i==0){
            for(int j=0; j<16; j++){
                Wall * bloc1 = new Wall();
                bloc1->setPos(i*bloc1->getWidth(),800 - (j+1) * bloc->getHeight());
                elementList->append(bloc1);
            }
        }

        if(i == 25){
            for(int j=0;j<3;j++){
                Enemy * enemy = new Enemy();
                enemy->setPos(i*bloc->getWidth(), 430 -(j+1) * enemy->getHeight());
                unitList->append(enemy);

                Enemy * enemy1 = new Enemy();
                enemy1->setPos(i*bloc->getWidth()-80, 430 - (j+1) * enemy1->getHeight());
                unitList->append(enemy1);
            }
        }

        if(i == 34 || i== 45 || i== 55 || i==65 || i==75 || i== 40 || i==70){
            MobileEnemy * mob = new MobileEnemy();
            mob->setPos(i*bloc->getWidth(),800 - mob->getHeight());
            unitList->append(mob);
        }
        if(i == 32){
            Wall * bloc2 = new Wall();
            bloc2->setPos(i*bloc->getWidth(),660 - bloc2->getHeight());
            elementList->append(bloc2);

            Wall * bloc3 = new Wall();
            bloc3->setPos(i*bloc->getWidth(),800 - bloc3->getHeight());
            elementList->append(bloc3);
        }
        delete bloc;
    }
    for (int i = 38;i<80;i++) {
        if(i != 47 && i != 48 && i !=46 ){
            Wall * bloc = new Wall();
            bloc->setPos(i*bloc->getWidth(),510);
            elementList->append(bloc);

            //torres de inimigos
            if(i==43){
                for(int j=0 ; j<8 ; j++){
                    Enemy * ene = new Enemy();
                    ene->setPos(i*bloc->getWidth()  - 100, 510 - (j+1) * ene->getHeight());
                    unitList->append(ene);
                }
            }
            if(i==44){
                for(int j=0 ; j<6 ; j++){
                    Enemy * ene = new Enemy();
                    ene->setPos(i*bloc->getWidth() - 50, 510  - (j+1) * ene->getHeight());
                    unitList->append(ene);
                }
            }
            if(i == 45){
                for(int j=0 ; j<4 ; j++){
                    Enemy * ene = new Enemy();
                    ene->setPos(i*bloc->getWidth(),510 - (j+1) * ene->getHeight());
                    unitList->append(ene);
                }
            }
            //fim
            if(i == 77){
                Finish *fim = new Finish();
                fim->setPos(i*bloc->getWidth(),510 - fim->getHeight());
                elementList->append(fim);
            }
        }
    }
    //parede final
    for(int i = 15; i >= 0; i--){
        Wall * bloc = new Wall();
        bloc->setPos(3950 ,800 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);
    }

    //plataforma
    for(int i = 5; i < 10; i++){
        if(i != 9){
            Wall * bloc = new Wall();
            bloc->setPos(i*bloc->getWidth() + 900 ,430);
            elementList->append(bloc);
        }
    }
    for(int i = 0; i >= 0; i--){
        Wall * bloc = new Wall();
        bloc->setPos(i*bloc->getWidth() + 1690 ,430);
        elementList->append(bloc);
    }
    //degrau
    Wall * bloc = new Wall();
    Wall * bloc1 = new Wall();
    bloc->setPos(500 ,660 - bloc->getHeight());
    bloc1->setPos(750 ,660 - bloc->getHeight());
    elementList->append(bloc);
    elementList->append(bloc1);

    //plataforma
    for(int i = 2; i >= 1; i--){
        Wall * bloc = new Wall();
        Wall * bloc1 = new Wall();
        Wall * bloc2 = new Wall();
        Wall * bloc3 = new Wall();
        bloc->setPos(550 ,660 - bloc->getHeight() - bloc->getHeight());
        bloc1->setPos(600 ,660 - bloc->getHeight() - i * bloc->getHeight());
        bloc2->setPos(650 ,660 - bloc->getHeight() - i * bloc->getHeight());
        bloc2->setPos(650 ,660 - bloc->getHeight() - i * bloc->getHeight());
        bloc3->setPos(700,660 - bloc->getHeight() - bloc->getHeight());
        elementList->append(bloc);
        elementList->append(bloc1);
        elementList->append(bloc2);
        elementList->append(bloc3);
    }
}

void Map::generateMap3()
{
    width = 500;
    height = 200;

    difficulty = 1;

    //background
    backgroundPath = ":/resources/images/backgrounds/War4.png";


    //cria jogador
    player = new Player();
    player->setPos(200,400);

    name = "Night Challenge";

    //parede
    for(int i = 15; i >= 0; i--){
        Wall * bloc = new Wall();
        bloc->setPos(0 ,950 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);
    }

    //andar de cima
    for(int i = 0; i < 20; i++){
        Wall * bloc = new Wall();
        bloc->setPos((i+1)*bloc->getWidth(),500);
        elementList->append(bloc);
    }

    //andar do meio
    for(int i = 0; i < 20; i++){
        Wall * bloc = new Wall();
        bloc->setPos((i+10)*bloc->getWidth(),700);
        elementList->append(bloc);
    }

    //chão
    for(int i = 0; i < 36; i++){
        if(i!=22 && i!=23){
            Wall * bloc = new Wall();
            bloc->setPos((i+1)*bloc->getWidth(),900);
            elementList->append(bloc);

            if(i==3){
                //pilha de inimigos 1
                for(int j = 0 ; j<3 ; j ++){
                    Enemy * enemy = new Enemy();
                    enemy->setPos((i+1)*bloc->getWidth(),900 - (j+1) * enemy->getHeight());
                    unitList->append(enemy);
                }
            }
            if(i==6){
                //pilha de inimigos 2
                for(int j = 0 ; j<3 ; j ++){
                    Enemy * enemy = new Enemy();
                    enemy->setPos((i+1)*bloc->getWidth(),900 - (j+1) * enemy->getHeight());
                    unitList->append(enemy);
                }
            }
            if(i==9){
                //pilha de inimigos 3
                for(int j = 0 ; j<3 ; j ++){
                    Enemy * enemy = new Enemy();
                    enemy->setPos((i+1)*bloc->getWidth(),900 - (j+1) * enemy->getHeight());
                    unitList->append(enemy);
                }
            }
        }
    }

    //segunda parede
    for(int i = 8; i >= 0; i--){
        Wall * bloc = new Wall();
        bloc->setPos(1500 ,750 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);
        if(i == 5){
            Wall * bloc2 = new Wall();
            bloc2->setPos(1500 + bloc->getWidth(),750 - i * bloc2->getHeight());
            elementList->append(bloc2);

        }
        if(i==1){
            //bloqueio
            for(int j=0 ; j<6 ; j++){
                Wall * ene = new Wall();
                ene->setPos(1500 + bloc->getWidth() + j*ene->getWidth(),750 - i * bloc->getHeight());
                elementList->append(ene);
            }
            MobileEnemy * mbene = new MobileEnemy();
            mbene->setPos(1500 + bloc->getWidth(),750 - i * bloc->getHeight() - mbene->getHeight());
            unitList->append(mbene);
        }
    }

    //terceira parede
    for(int i = 0 ; i<13 ; i++){
        Wall * bloc = new Wall();
        bloc->setPos(1800 ,50 + i * bloc->getHeight());
        elementList->append(bloc);
    }

    //plataforma 1
    for(int i=0 ; i<30 ; i++){
        Wall * bloc = new Wall();
        bloc->setPos(2000 + i*bloc->getWidth() ,900);
        elementList->append(bloc);
        // border
        if(i == 0 || i == 29){
            Wall * bloc2 = new Wall();
            bloc2->setPos(2000 + i*bloc->getWidth() ,900 - bloc->getHeight());
            elementList->append(bloc2);
        }
        //inimigo móvel
        if(i == 1){
            MobileEnemy * mobEne = new MobileEnemy();
            mobEne->setPos(2000 + i*bloc->getWidth() ,900 - mobEne->getHeight());
            unitList->append(mobEne);
        }
        //inimigo móvel
        if(i == 10){
            MobileEnemy * mobEne = new MobileEnemy();
            mobEne->setPos(2000 + i*bloc->getWidth() ,900 - mobEne->getHeight());
            unitList->append(mobEne);
        }
        if(i == 15){
            MobileEnemy * mobEne = new MobileEnemy();
            mobEne->setPos(2000 + i*bloc->getWidth() ,900 - mobEne->getHeight());
            unitList->append(mobEne);
        }
        if(i == 20){
            MobileEnemy * mobEne = new MobileEnemy();
            mobEne->setPos(2000 + i*bloc->getWidth() ,900 - mobEne->getHeight());
            unitList->append(mobEne);
        }
    }
    //quinta plataforma
    for(int i=0 ; i<30 ; i++){
        Wall * bloc = new Wall();
        bloc->setPos(3800 + i*bloc->getWidth() ,750);
        elementList->append(bloc);
        // border
        if(i == 0 || i == 29){
            Wall * bloc2 = new Wall();
            bloc2->setPos(3800 + i*bloc->getWidth() ,750 - bloc->getHeight());
            elementList->append(bloc2);
        }
        //inimigos móveis
        if(i == 1 || i==10 || i==20){
            MobileEnemy * mobEne = new MobileEnemy();
            mobEne->setPos(3800 + i*bloc->getWidth() ,750 - mobEne->getHeight());
            unitList->append(mobEne);
        }
    }
    //plataforma
    for(int i=0 ; i<30 ; i++){
        Wall * bloc = new Wall();
        bloc->setPos(5600 + i*bloc->getWidth() ,600);
        elementList->append(bloc);
        //borda
        if(i == 0 || i == 29){
            Wall * bloc2 = new Wall();
            bloc2->setPos(5600 + i*bloc->getWidth() ,600 - bloc->getHeight());
            elementList->append(bloc2);
            if(i==29){
                Finish * fim = new Finish();
                fim->setPos(5600 + i*bloc->getWidth() ,600 - bloc->getHeight() - fim->getHeight());
                elementList->append(fim);
            }
        }
        //inimigos móveis
        if(i == 1 || i==10 || i==15 || i==20 || i == 25){
            MobileEnemy * mobEne = new MobileEnemy();
            mobEne->setPos(5600 + i*bloc->getWidth() ,600 - mobEne->getHeight());
            unitList->append(mobEne);
        }
        //pilha de inimigos
        if(i == 15){
            for(int j=0; j<3 ; j++){
                Enemy * enemy = new Enemy();
                enemy->setPos(5600 + (i+1)*bloc->getWidth(),600 - (j+1) * enemy->getHeight());
                unitList->append(enemy);
            }
        }
    }
}
bool Map::readmap(QString directory)
{
    //limpa o mapa atual se existir
    clearMap();

    QString path = QStringLiteral("levels/%1/map.json").arg(directory);
    QFile loadFile(path);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return false;
    }

    //lê dados
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    //transforma para json
    QJsonObject mapJson = loadDoc.object();

    //lê elementos json
    height = mapJson["height"].toInt();
    width = mapJson["width"].toInt();
    difficulty = mapJson["difficulty"].toInt();

    backgroundPath = mapJson["background"].toString();
    background = QImage(backgroundPath);
    background = background.scaledToHeight(height);

    QJsonArray elemTab = mapJson["elem"].toArray();
    for (int index = 0; index < elemTab.size(); ++index) {
        QJsonObject elem = elemTab[index].toObject();
        if(elem["type"].toString() == "player"){
            player = new Player();
            player->setX(elem["x"].toInt());
            player->setY(elem["y"].toInt());
        }
        if(elem["type"].toString() == "wall"){
            Wall * w = new Wall();
            w->setX(elem["x"].toInt());
            w->setY(elem["y"].toInt());
            elementList->append(w);
        }
        if(elem["type"].toString() == "enemy"){
            Enemy * e = new Enemy();
            e->setX(elem["x"].toInt());
            e->setY(elem["y"].toInt());
            unitList->append(e);
        }

        if(elem["type"].toString() == "finish"){
            Finish * fim = new Finish();
            fim->setX(elem["x"].toInt());
            fim->setY(elem["y"].toInt());
            elementList->append(fim);
        }
        if(elem["type"].toString() == "mobileEnemy"){
            MobileEnemy * mbEne = new MobileEnemy();
            mbEne->setX(elem["x"].toInt());
            mbEne->setY(elem["y"].toInt());
            unitList->append(mbEne);
        }
    }
    loadFile.close();
    return true;
}

void Map::clearMap()
{
    if(player != NULL){
        delete player;
        player = NULL;
    }


    for(Element * elem : *elementList){
        delete elem;
    }
    elementList->clear();

    for(Unit * unit: *unitList){
        delete unit;
    }
    unitList->clear();


}

bool Map::saveMap(QString directory)
{
    //Abre o arquivo
    QDir dir =  QStringLiteral("levels/%1").arg(directory);;
    QString path = QStringLiteral("levels/%1/map.json").arg(directory);
    QFile saveFile(path);
    qDebug() << dir.absolutePath();
    QDir dirLevel = QString("levels");

    //cria diretório das fases caso não exista
    if(!dirLevel.exists()){
        QDir().mkdir(QString("levels"));
    }

    //cria diretório dos mapas caso não exista
    if(!dir.exists()){
        QDir().mkdir( QStringLiteral("levels/%1").arg(directory));
    }

    //Abre o arquivo e cria se não existir
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject mapJson;
    QJsonArray jsonTab;

    mapJson["height"] = height;
    mapJson["width"] = width;
    mapJson["background"] = backgroundPath;
    mapJson["difficulty"] = difficulty;


    foreach (Element * elem, *elementList) {
        QJsonObject jsonObject;
        jsonObject["type"] = elem->getType();
        jsonObject["x"] = elem->x();
        jsonObject["y"] = elem->y();
        jsonTab.append(jsonObject);
    }
    foreach (Element * elem, *unitList) {
        QJsonObject jsonObject;
        jsonObject["type"] = elem->getType();
        jsonObject["x"] = elem->x();
        jsonObject["y"] = elem->y();
        jsonTab.append(jsonObject);
    }

    QJsonObject playerJson;
    playerJson["type"] = player->getType();
    playerJson["x"] = player->x();
    playerJson["y"] = player->y();
    jsonTab.append(playerJson);
    mapJson["elem"] = jsonTab;

    //Salva e escreve mapJson
    QJsonDocument saveDoc(mapJson);
    saveFile.write(saveDoc.toJson());

    saveFile.close();
    return true;
}

QList<Element *> * Map::getElementList() const
{
    return elementList;
}

Player *Map::getPlayer() const
{
    return player;
}

Finish *Map::getFinish() const{
    return finish;
}

QImage Map::getBackground() const
{
    return background;
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

void Map::setBackground(const QImage &value)
{
    background = value.scaledToHeight(height);
}

QList<QString> Map::getLevels()
{
    QList<QString> list;
    QDirIterator iterator("levels");
    QMap<int,QString> listSorted;
    while (iterator.hasNext()) {
        QString dir = iterator.next();
        dir.remove("levels/");
        if(dir != "." && dir != ".."){
            Map* temp = new Map();
            temp->readmap(dir);
            int dif = temp->getDifficulty();
            listSorted.insert(dif,dir);
        }
    }
    foreach(QString value,listSorted){
        list.append(value);
    }
    return list;
}

QString Map::getName() const
{
    return name;
}

int Map::getDifficulty() const
{
    return difficulty;
}


QList<Unit *> * Map::getUnitList() const
{
    return unitList;
}

