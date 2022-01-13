#ifndef GAMETIME_H
#define GAMETIME_H

#include <QElapsedTimer>


/**
 * @brief Classe contenant des méthodes de classe utiles pour calculer le temps entre chaque frame
 * @author Pierre.L
 * @version 0.1
 * @date 05 janv 2021
 *
 * Header de la classe boundingBox
 *
 */
class GameTime{
private :
    inline static double deltaTime = 0;
    inline static QElapsedTimer lastFrame = QElapsedTimer();
    GameTime(){}
public :

    /*!
     *  \brief Methode de classe qui permet d'initialiser le compteur
     */
    static void initGameTime(){
        lastFrame.start();
        deltaTime = 0;
    }

    /*!
     *  \brief Methode de classe qui permet de notifier qu'une nouvelle frame a commencé
     */
    static void notifyNewFrame(){
        deltaTime = lastFrame.elapsed()/1000.0;
        lastFrame.start();
    }
    /*!
     *  \brief Retourne le temps écoulé à la dernière frame
     */
    static double getDeltaTime(){
        return deltaTime;
    }
};

#endif // GAMETIME_H
