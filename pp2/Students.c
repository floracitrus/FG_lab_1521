   // Students.c ... implementation of Students datatype
  
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <string.h>
    #include <assert.h>
    #include "Students.h"
    #define BUFFSIZE 100
    typedef struct _stu_rec {
            int   id;
            char  name[20];
            int   degree;
            float wam;
    } sturec_t;
  
    typedef struct _students {
        int    nstu;
        StuRec recs;
    } students_t;
  
    // read text from input (FILE *)
    // write sturec_t structs to output (filedesc)
    int makeStuFile(char *inFile, char *outFile)
    {
        FILE* input = fopen(inFile, "r");
        if(input == NULL) return -1;
            int output = open(outFile, O_CREAT|O_WRONLY, 0644);
        if(output < 0) return -2;
  
        StuRec stu;
        while( fscanf(input, "%d %s %d %f", &stu.id, stu.name, &stu.degree, &stu.wam) > 0 ){
        
            int retval = write(output, &stu, sizeof(struct _stu_rec));
            if(retval < sizeof(struct _stu_rec)) return -3;
            showStuRec(stu);
        }
  
  
  
  
       // char buf[BUFSIZE];
      //  while( fgets(buf,sizeof(struct _stu_rec), input) != NULL){
       //     fprintf(output, "%d %s %d %f \n", stu->id, stu->name, stu->degree, stu->wam);
      //  }
  
  
  
        //while(read(input, &stu, sizeof(struct _stu_rec)) > 0){
        //    fscanf(input, "%d %s %d %f", &stu->id, stu->name, &stu->degree, &stu->wam);
        //    write(output, stu, sizeof(struct _stu_rec));
           //showStuRec(stu);
        //}
        close(output);
            fclose(input);
            return 0;
  
    }
  
    // build a collection of student records from a file descriptor
    Students getStudents(int in)
    {
        int ns;  // count of #students
  
            // Make a skeleton Students struct
            Students ss;
            if ((ss = malloc(sizeof (struct _students))) == NULL) {
                    fprintf(stderr, "Can't allocate Students\n");
                    return NULL;
            }
  
            // count how many student records
        int stu_size = sizeof(struct _stu_rec);
        sturec_t s;
            ns = 0;
        while (read(in, &s, stu_size) == stu_size) ns++;
        ss->nstu = ns;
        if ((ss->recs = malloc(ns*stu_size)) == NULL) {
                    fprintf(stderr, "Can't allocate Students\n");
                    free(ss);
                    return NULL;
            }
  
            // read in the records
            lseek(in, 0L, SEEK_SET);
            for (int i = 0; i < ns; i++)
                    read(in, &(ss->recs[i]), stu_size);
  
            close(in);
            return ss;
    }
  
    // show a list of student records pointed to by ss
    void showStudents(Students ss)
    {
            assert(ss != NULL);
            for (int i = 0; i < ss->nstu; i++)
                    showStuRec(&(ss->recs[i]));
    }
  
    // show one student record pointed to by s
    void showStuRec(StuRec s)
    {
            printf("%7d %s %4d %0.1f\n", s->id, s->name, s->degree, s->wam);
    }




//prac sample paper flora selfmade not sure correctness yet
    void sortByName(Students ss){
        assert(ss!=NULL);
        do {
            int nswaps = 0;
            for (i=1;i<n-1;i++) {
                if(ss[i] < ss[i-1]) {
                    Studnets temp = ss[i];
                    ss[i]= ss[i-1];
                    ss[i-1]= temp;
                    nswaps++;
                }
            }
        } while (nswaps > 0);
    }







