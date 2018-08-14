#ifndef CONSTMATRICES_H
#define CONSTMATRICES_H

#include <QGenericMatrix>

const double initValuesProjecten3dTo2d[] = {1,0,0,0,1,0};

//Orthogonal projection
const QGenericMatrix<3,2,double> projection3dTo2D(initValuesProjecten3dTo2d);

//Stereographic projection
const QGenericMatrix<3,2,double> projectionStero(const double scale){
    double z = 1.0 / (1 - scale);
    double v[]= {z,0,0,0,z,0};
    return QGenericMatrix<3,2,double>(v);
}

const QGenericMatrix<4,2, double> projection4dTo2D(){
    const double v[] = {
        1, 0, 0, 0,
        0, 1, 0, 0
    };
    return QGenericMatrix<4,2, double>(v);
}

const QGenericMatrix<4,3, double> projection4dTo3D(const double scale){
    double z = 1.0 / (1 - scale);
    const double v[] = {
        z, 0, 0, 0,
        0, z, 0, 0,
        0, 0, z, 0
    };
    return QGenericMatrix<4,3, double>(v);
}

const QGenericMatrix<3,3,double> rotation3dX(const double angle){
    double values[] ={
        1, 0, 0,
        0, cos(angle), -sin(angle),
        0, sin(angle),  cos(angle)
    };

    return QGenericMatrix<3,3,double>(values);
}

const QGenericMatrix<3,3,double> rotation3dY(const double angle){
    double values[] ={
        cos(angle), 0, sin(angle),
        0, 1, 0,
       -sin(angle), 0, cos(angle)
    };

    return QGenericMatrix<3,3,double>(values);
}

const QGenericMatrix<3,3,double> rotation3dZ(const double angle){
    double values[] ={
        cos(angle), -sin(angle), 0,
        sin(angle),  cos(angle), 0,
        0, 0, 1
    };

    return QGenericMatrix<3,3,double>(values);
}

const QGenericMatrix<4,4,double> rotation4dXY(const double angle){
    double v[] = {
        1,  0,  0,  0,
        0,  1,  0,  0,
        0,  0,  cos(angle), -sin(angle),
        0,  0,  sin(angle), cos(angle)
    };
    return QGenericMatrix<4,4,double> (v);
}

const QGenericMatrix<4,4,double> rotation4dXW(const double angle){
    double v[] = {
        1,  0,          0,              0,
        0,  cos(angle), -sin(angle),    0,
        0,  sin(angle),  cos(angle),    0,
        0,  0,          0,              1
    };
    return QGenericMatrix<4,4,double> (v);
}

const QGenericMatrix<4,4,double> rotation4dYZ(const double angle){
    double v[] = {
        cos(angle), 0, 0,  -sin(angle),
        0,          1,  0,  0,
        0,          0,  1,  0,
        sin(angle), 0, 0,   cos(angle),  0
    };
    return QGenericMatrix<4,4,double> (v);
}

const QGenericMatrix<4,4,double> rotation4dZW(const double angle){
    double v[] = {
        cos(angle), -sin(angle), 0, 0,
        sin(angle), cos(angle),  0, 0,
        0,          0,  1,  0,
        0,          0,  0,  1,
    };
    return QGenericMatrix<4,4,double> (v);
}

const QGenericMatrix<4,4,double> rotation4dYW(const double angle){
    double v[] = {
        cos(angle), 0, -sin(angle), 0,
        0,          1,  0,  0,
        sin(angle), 0,  cos(angle), 0,
        0,          0,  0,  1,
    };
    return QGenericMatrix<4,4,double> (v);
}

const double distance(const QGenericMatrix<1,3,double> &a, const QGenericMatrix<1,3,double> &b){
    return pow(double((a.constData()[0] - b.constData()[0]) * (a.constData()[0] - b.constData()[0]) +
                      (a.constData()[1] - b.constData()[1]) * (a.constData()[1] - b.constData()[1]) +
                      (a.constData()[2] - b.constData()[2]) * (a.constData()[2] - b.constData()[2])),double(0.5));
}

const double distance(const QGenericMatrix<1,4,double> &a, const QGenericMatrix<1,4,double> &b){
    return pow(((a.constData()[0] - b.constData()[0]) * (a.constData()[0] - b.constData()[0]) +
                (a.constData()[1] - b.constData()[1]) * (a.constData()[1] - b.constData()[1]) +
                (a.constData()[2] - b.constData()[2]) * (a.constData()[2] - b.constData()[2]) +
                (a.constData()[3] - b.constData()[3]) * (a.constData()[3] - b.constData()[3])),0.5);
}
#endif // CONSTMATRICES_H
