#include "backend.h"
#include "matrices.h"

#include <QTimer>

const int centerX = 400;
const int centerY = 400;
const int length = 1;

Backend::Backend(QObject *parent) : QObject(parent)
{
    m_Dimension = Dim4;
    createCube();

    QTimer *t(new QTimer(this));
    connect(t, &QTimer::timeout, this, &Backend::updatePoints);

    //~66Hz
    t->start(15);
}

void Backend::updatePoints()
{
    m_Tesseract.clear();
    if(m_Dimension == Dim3){
        auto rotX = rotation3dX(angle);
        auto rotY = rotation3dY(angle);
        auto rotZ = rotation3dZ(angle);

        auto rotTotal = rotZ * rotY * rotX;

        QVector<QVector3D> v;
        for(const QGenericMatrix<1,3,double> &matrix : m_VectorMatices3d){
            m_Tesseract << matrixToVector2d( rotTotal * matrix);
            v << matrixToVector3d(rotTotal * matrix);
        }
        emit newCube(v,m_nNeighbours);

    } else if( m_Dimension == Dim4){
        auto rotZW = rotation4dZW(angle);
        auto rotXY = rotation4dXY(angle);
        auto rotYW = rotation4dYW(angle);
        auto rotXW = rotation4dXW(0);
        auto rotYZ = rotation4dYZ(0);
        auto rotTotal = rotZW * rotXY * rotYW * rotYZ * rotXW;

        QVector<QVector3D> v;
        for(const QGenericMatrix<1,4, double> &matrix : m_VectorMatices4d){
            m_Tesseract << matrixToVector2d(rotTotal * matrix);
            v << matrixToVector3d(rotTotal * matrix);
        }
        emit newCube(v,m_nNeighbours, false);
    }

    angle += 0.02;

    emit tesseractChanged();
}

QVector2D Backend::matrixToVector2d(const QGenericMatrix<1, 3, double> &matrix)
{
    //Orthogonal projection
//!    const QGenericMatrix<1,2,double> m2d = projection3dTo2D * matrix;

    //Stereographic Projection
    const QGenericMatrix<1,2,double> m2d = projectionStero(matrix.constData()[2]/200) * matrix;

    return QVector2D(static_cast<float>(m2d.constData()[0] + centerX), static_cast<float>(m2d.constData()[1] + centerY));
}

QVector2D Backend::matrixToVector2d(const QGenericMatrix<1, 4, double> &matrix)
{
    //4d to 3d
    auto dim3d = projection4dTo3D(matrix.constData()[3]/*/20.0*/) * matrix;

    //Static rotation -> "Camera angle"
    dim3d = rotation3dY(0.785) * rotation3dX(0.785) * dim3d;

    //Orthogonal projection
    const QGenericMatrix<1,2,double> m2d = projection3dTo2D * dim3d;

    //Stereographic Projection
//!    const QGenericMatrix<1,2,double> m2d = projectionStero(dim3d.constData()[2]/270.0) * dim3d;

    return QVector2D(static_cast<float>(m2d.constData()[0] + centerX), static_cast<float>(m2d.constData()[1] + centerY));
}

QVector3D Backend::matrixToVector3d(const QGenericMatrix<1, 3, double> &matrix)
{
    return QVector3D (static_cast<float>(matrix.constData()[0]),static_cast<float>(matrix.constData()[1]),static_cast<float>(matrix.constData()[2]));
}

QVector3D Backend::matrixToVector3d(const QGenericMatrix<1, 4, double> &matrix)
{
    auto dim3d = projection4dTo3D(matrix.constData()[3]/200.0) * matrix;
    dim3d = rotation3dY(0.785) * rotation3dX(0.785) * dim3d;
    return QVector3D (static_cast<float>(dim3d.constData()[0]),static_cast<float>(dim3d.constData()[1]),static_cast<float>(dim3d.constData()[2]));
}

void Backend::createCube()
{
    for( int i(0); i < 2; i++){
        for( int j(0); j < 2; j++){
            for( int k(0); k < 2; k++){
                if(m_Dimension == Dim3) {
                    createVector( i ? length : -length,
                                  j ? length : -length,
                                  k ? length : -length);
                } else if (m_Dimension == Dim4) {
                    for( int l(0); l < 2; l++)
                        createVector( i ? length : -length,
                                      j ? length : -length,
                                      k ? length : -length,
                                      l ? length : -length);
                }
            }
        }
    }
    createNN();
}

void Backend::createVector(const double x, const double y, const double z)
{
    double v[]= {x,y,z};
    m_VectorMatices3d << QGenericMatrix<1,3,double>(v);
}

void Backend::createVector(const double x, const double y, const double z, const double w)
{
    double v[]= {x,y,z,w};
    m_VectorMatices4d << QGenericMatrix<1,4,double>(v);
}

void Backend::createNN()
{
    if(m_Dimension == Dim3) {
        for(const QGenericMatrix<1,3,double> &a : m_VectorMatices3d){
            QList<int> nn;
            for(int i(0); i < m_VectorMatices3d.size(); i++){
                if(abs(distance(a,m_VectorMatices3d.at(i)) - (2 * length)) < 0.01)
                    nn << i;
            }
            m_nNeighbours << nn;
        }
    } else if(m_Dimension == Dim4) {
        for(const QGenericMatrix<1,4,double> &a : m_VectorMatices4d){
            QList<int> nn;
            for(int i(0); i < m_VectorMatices4d.size(); i++){
                if(abs(distance(a,m_VectorMatices4d.at(i)) - (2* length)) < 0.01)
                    nn << i;
            }
            m_nNeighbours << nn;
        }
    }
}
