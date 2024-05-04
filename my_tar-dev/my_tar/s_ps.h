typedef struct s_ps {
        char **av, *av_i, *av_i_d, *t, *z, *buf, *buf2, *s;
        DIR *dp;
        struct dirent *dl;
        struct stat *b, *b2;
        lln *h;
	os o;
        long ts, tn;
        int ac, fd, er, oc, i;
        bool sw;
} ps ;
