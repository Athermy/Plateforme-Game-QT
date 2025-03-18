#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <qscrollbar.h>
#include <QGraphicsPixmapItem>
#include <QSignalMapper>
#include <QApplication>
#include <QGraphicsProxyWidget>

#include "map.h"
#include "menu.h"
#include "pausegroup.h"
#include "victorygroup.h"

class GameEngine: public QGraphicsView{
    Q_OBJECT

public:
    //Inicializa o jogo
    GameEngine();

    //Remove todos os objetos do jogo
    ~GameEngine();

    //movimentos do player
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    //Escala o mapa conforme o tamanho da janela, é ativado quando o tamanho da janela muda
    void resizeEvent(QResizeEvent *event) override;

    //atualiza a posição do player durante o jogo
    void updatePlayerPosition();

    //respawna o player no começo do jogo
    void respawn();

    //atualiza a posição da câmera
    void updateCamera();

    //mostra os elementos
    void drawElements();

    //atualiza a posição dos projéteis
    void updateProjectilePosition();

    //atualiza a posição vertical dos inimigos fixos
    void updateEnemyPosition();

    //atualiza a posição dos inimigos móveis
    void updateMobileEnemyPosition();

    //abre o jogo
    void openGame();

    //pausa o jogo
    void openPause();

    //deleta os objetos usados na criação da fase
    void clearLevel();

    //dá game over
    void gameOver();

    //seta um timer para o menu de pause
    void pauseTimer();

    //continua o jogo depois do pause
    void resumeTimer();

    //mostra o menu de vitória
    void victory();

    //fecha o menu de vitória
    void closeVictory();

    //toca a música da fase
    void playMusic(QString qrcPath);

    //retorna se espaço foi pressionado
    bool getspacePressed();

public slots:

    //atualiza a posição de todos os elementos
    void updateAllPositions();

    //carrega a fase
    void loadMap(QString worldName);

    //faz as animações do player
    void animate();

    //carrega novamente a fase
    void retryMap();

    //remove o modo pausado
    void closePause();

    //abre o menu
    void openMenu();

    //sai do jogo
    void quitApp();

    //reinicia o jogo
    void restart();

private:

    //cena do jogo
    QGraphicsScene * levelScene;

    //background do jogo
    QImage background;

    //mapa do jogo
    Map * map;

    //largura da janela do jogo
    int windowWidth;

    //altura da janela do jogo
    int windowHeight;

    //número do sprite para fazer a animação
    int playerSprite;

    int playerStaticCounter;

    QGraphicsItemGroup * worldPlan;

    //menu principal do jogo
    Menu * menuScene;

    //timers para gerenciar as animações
    QTimer * Animtimer;

    //número de FPS
    QTimer * refreshTimer;

    //intervalo antes de respawnar o player
    QTimer * restartTimer;

    //mapeamento dos botões do menu
    QSignalMapper * buttonMenuMapper;

    //menu de pausa do jogo
    PauseGroup * pauseMenu;

    //menu de vitória do jogo
    VictoryGroup * victoryMenu;

    QGraphicsProxyWidget * continueProxy;

    QGraphicsProxyWidget * backMenuProxy;

    //true se pausado
    bool paused;

    //true se concluído
    bool finished;

    //true se o espaço é pressionado
    bool spacePressed;

    //tempo restante para o timer
    int overRemainTime;

    //tempo restante para a imunidade
    int immuneRemainTime;
};


#endif // GAMEENGINE_H
