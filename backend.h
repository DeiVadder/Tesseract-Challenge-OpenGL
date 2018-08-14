#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QVector>
#include <QVector2D>
#include <QVector3D>

#include <QGenericMatrix>

Q_DECLARE_METATYPE(QVector2D)
Q_DECLARE_METATYPE(QList<QVector2D>)
Q_DECLARE_METATYPE(const double *)

class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(QObject *parent = nullptr);

    enum CubeDimension{
        Dim3 = 0,
        Dim4
    };
    Q_ENUM(CubeDimension)

    Q_INVOKABLE QVector2D getPoint(const int index){
        if(index < m_Tesseract.size())
            return m_Tesseract.at(index);
        return QVector2D(0,0);
    }

    Q_INVOKABLE QList<int> getNearest(const int index){return m_nNeighbours.at(index);}

    Q_INVOKABLE inline bool is4D(){ return m_Dimension == Dim4;}
signals:
    void tesseractChanged();

    void newCube(const QVector<QVector3D> &v, const QList<QList<int> > &nn, bool dim3 = true);

public slots:
    void updatePoints();

private:
    QVector2D matrixToVector2d(const QGenericMatrix<1,3,double> &matrix);
    QVector2D matrixToVector2d(const QGenericMatrix<1,4,double> &matrix);

    QVector3D matrixToVector3d(const QGenericMatrix<1,3,double> &matrix);
    QVector3D matrixToVector3d(const QGenericMatrix<1,4,double> &matrix);

    void createCube();

    void createVector(const double x, const double y, const double z);
    void createVector(const double x, const double y, const double z, const double w);

    void createNN();

protected:
    QList<QVector2D> m_Tesseract;

    QList<QList<int> > m_nNeighbours;

    QVector<QGenericMatrix<1,3,double> > m_VectorMatices3d;
    QVector<QGenericMatrix<1,4,double> > m_VectorMatices4d;

    double angle = 0;

    CubeDimension m_Dimension = Dim3;

    QVector<quint64> m_Ms;
};

#endif // BACKEND_H
