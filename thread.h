#ifndef THREAD_H
#define THREAD_H

#include "QThread"


class cthread : public QThread
{
    Q_OBJECT
public:
    cthread();
protected:
    void run() override;
};

#endif // THREAD_H
