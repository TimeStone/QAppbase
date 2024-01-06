#include "utils.h"

Utils::Utils(QObject *parent) : QObject(parent)
{

}

void Utils::crashIt(){
    int *a = (int *) (NULL);
    *a = 1; //must crash here!
}
