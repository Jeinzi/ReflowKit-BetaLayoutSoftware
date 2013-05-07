#ifndef REFLOWCONTROLLER_H
#define REFLOWCONTROLLER_H

#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <QRegExp>
#include <QObject>
#include <QStringList>
#include <QVector>
#include <fstream>

#include "uart.h"

using namespace std;

class ReflowController : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief MAX_SIZE_TEMP_LIST maximum number of tmeps to memorized. i.e the maximum item inside QVector<double> _temps/_times.
     */
    static int MAX_SIZE_TEMP_LIST;


    ReflowController( QObject *parent = 0);


    /**
     * @brief openDevice open the given device, using SR232 and a specified baudrate.
     * @param path device path to open (such as /dev/ttyUSB0 for linux or COM4 for Win)
     * @return
     */
    bool openDevice( string path );
    /**
     * @brief closeDevice close the opened deviced (Uart)
     */
    void closeDevice();
    /**
     * @brief getUartDevice
     * @return Pointer to the current Uart object.
     */
    Uart* getUartDevice();
    /**
     * @brief exportCVS save datas (_temps an _times) to the specified file, with CVS format.
     * @param path path to the file to save
     * @param separator the separator for CVS format
     */
    void exportCVS(string path, char separator);


    /**
     * @brief startLearning Ask the Reflowkit to start the learning process by sending the good command.
     */
    void startLearning();

    /**
     * @brief checkUartDataReady Check if some Uart data are ready. If yes, then datas are stored inside _datas buffer, and the Uart is cleared.
     */
    void checkUartDataReady();
    /**
     * @brief parseUart Parse the given data. Search for Config command and Temp command.
     * @param data data to parse (list of commands)
     */
    void parseUart(string data);

    void setPhtTemp( int v );
    void setPhtTime( int v );
    void setPhtPwr( int v );

    void setSoakTemp( int v );
    void setSoakTime( int v );
    void setSoakPwr( int v );

    void setReflowTemp( int v );
    void setReflowTime( int v );
    void setReflowPwr( int v );

    void setDwellTemp( int v );
    void setDwellTime( int v );
    void setDwellPwr( int v );

    void setTempoffset( int v );
    void setTempShow( int v );

    int getPhtTemp(  ) const;
    int getPhtTime(  ) const;
    int getPhtPwr(  ) const;

    int getSoakTemp(  ) const;
    int getSoakTime(  ) const;
    int getSoakPwr(  ) const;

    int getReflowTemp(  ) const;
    int getReflowTime(  ) const;
    int getReflowPwr(  ) const;

    int getDwellTemp( ) const;
    int getDwellTime( ) const;
    int getDwellPwr(  ) const;

    int getTempoffset(  ) const;
    int getTempShow( ) const;

    int getCurrentTemp();
    QVector<double>* getTemps();
    QVector<double>* getTimes();

    /**
     * @brief addTemp add the given temp and time inside _temps and _times QVector.
     * @param temp temperature to add.
     * @param time time of the given temperature to add.
     */
    void addTemp(double temp , double time);

    /**
     * @brief getDatas return a QStringList representing the few last  uart command received
     * @return
     */
    QStringList* getDatas();
public slots:
    /**
     * @brief updateInformation  send the "showall" command, so the reflowController can parse the configuration received
     */
    void updateInformation();

private:
    int _phttemp;
    int _phttime;
    int _phtpwr;

    int _soaktemp;
    int _soaktime;
    int _soakpwr;

    int _reflowtemp;
    int _reflowtime;
    int _reflowpwr;

    int _dwelltemp;
    int _dwelltime;
    int _dwellpwr;

    int _tempoffset;
    int _tempshow;

    int _currentTemp;
    Uart* _uart;
    static int MAX_DATAS_STORED;
    QStringList* _datas;
    QVector<double> _temps;
    QVector<double> _times;

};

#endif // REFLOWCONTROLLER_H
