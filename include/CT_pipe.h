//
// Created by Gustavo Viegas on 2017/06
//

#ifndef CT_PIPE_H
#define CT_PIPE_H

// Open named pipe for reading
//
int ctNpipeIn(char* path);

// Open named pipe for writing
//
int ctNpipeOut(char* path);

#endif // CT_PIPE_H
