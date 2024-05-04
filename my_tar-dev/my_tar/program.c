# include "header.h"

ps allocate (ps p) {
	p.fd = 0;	p.er = 0;	p.oc = 0;
	p.ts = 0;	p.sw = 0;
	p.o.l = malloc(sizeof (char) * 8);
	p.o.l = my_strcp ("-crtuxf", p.o.l, 0);
	p.o.s = malloc(sizeof (bool) * 8);
	for (int i = 0; i < 8; i++) { p.o.s[i] = 0; }
	p.z = malloc(sizeof (char) * 1024);
	for (int i = 0; i < 1024; i++) { p.z[i] = 0; }
	p.buf = malloc(sizeof (char) * 512);
	for (int i = 0; i < 512; i++) { p.buf[i] = 0; }
	p.buf2 = malloc(sizeof (char) * 512);
	for (int i = 0; i < 512; i++) { p.buf2[i] = 0; }
	p.av_i_d = malloc(sizeof (char) * 100);
	for (int i = 0; i < 100; i++) { p.av_i_d[i] = 0; }
	p.b = malloc(sizeof (struct stat));
	p.b2 = malloc(sizeof (struct stat));
	p.h = malloc(sizeof(lln));
	p.h->nm = malloc(sizeof (char) * 100);
	for (int i = 0; i < 100; i++) { p.h->nm[i] = 0; }
	p.h->nx = NULL;
	p.av_i = NULL;
	return p;
}

int cant (char *s1) {
	if ( !nsf(s1) ) return 0;
	int i = my_strlen(s1);
	char *s2 = malloc(sizeof(char) * ( i + 52 ) );
	my_strcp("my_tar: ", s2, 0);
	my_strcp(s1, s2, 8);
	my_strcp(": Cannot stat: ", s2, 8 + i );
	my_strcp("No such file or directory\n", s2, 23 + i );
	write (2, s2, 51 + i );
	free(s2);
	return 1;
}

ps c (ps p) {
	bool b = 0;
	if(p.o.s[1]){
	p.fd = open (p.av[2], O_CREAT|O_WRONLY|O_TRUNC, 00600);
	} else if ( (p.o.s[2]) ) {
		p.fd = open (p.av[2], O_WRONLY);
		lseek( p.fd, -1024, SEEK_END);
	} else if (p.o.s[4]) {
		p.fd = open (p.av[2], O_RDWR);
		p = tl (p);
		lseek( p.fd, -1024, SEEK_END);
	}
	for ( int i = 3; i < p.ac; i++ ) {
		if ( !cant(p.av[i]) ) {
			p.av_i = p.av[i];
			if ( (p.o.s[4]) && tc (p)) return p;
			lstat (p.av_i, p.b);
			p = crw (p);
			b = 1;
		}
	}
	if (b) write (p.fd, p.z, 1024);
        close (p.fd);
	return p;
}

ps check_args (ps p) {
	if ((p.er = nma (p.ac, 3)) == 2) {
		return p;
	}
	p = fill_pos(p);
	p = p_opt_er(p);
	return p;
}

crws chksum (crws cs) {
	for (int i = 0; i < 512; i++) {
		cs.ch += cs.buf[i];
	}
	cs.j = cs.ch;
	cs.k = 6;
	cs = oct (cs);
	my_strcp (cs.oct, cs.buf, 148);
	return cs;
}

crws crw_all (ps p, crws cs) {
        cs.bs = 1;	cs.fd2 = 0;	cs.i = 0;
	cs.j = 0;	cs.k = 0;	cs.ch = 0;
	cs.c = 0;	cs.sw = p.sw;	cs.fd = p.fd;
	int i = my_strlen(p.av_i) + 1;
	cs.av_i = malloc(sizeof (char) * i);
	my_strcp (p.av_i, cs.av_i, 0);
      	cs.av_i_d = malloc(sizeof (char) * 100);
	my_strcp (p.av_i, cs.av_i_d, 0);
	if ( p.sw ) {
		cs.av_i_d[i-1] = '/';
		my_strcp (p.dl->d_name, cs.av_i_d, i);
	}
        cs.buf = malloc(sizeof (char) * 512);
        for (i = 0; i < 512; i++) { cs.buf[i] = 0; }
        cs.b = malloc(sizeof (struct stat));
        cs.oct = malloc ( sizeof(char) * 12 );
        for (i = 0; i < 12; i++) { cs.oct[i] = 0; }
	cs.z = malloc(sizeof (char) * 1024);
	for (int i = 0; i < 1024; i++) { cs.z[i] = 0; }
	return cs;
}

ps crw (ps p) {
	crws cs = crw_all ( p, cs );
	if ( p.sw ) { cs.fd2 = open (cs.av_i_d, O_RDONLY);
        } else 	      cs.fd2 = open (cs.av_i,   O_RDONLY);
        if (cs.fd2 == -1) {
		printf("Can't read file\n");
        	return p;
	}
	cs = wh(cs);
	write (p.fd, cs.buf, 512);
	cs = wb(cs);
        for (int i = 0; i < 512; i++) { cs.buf[i] = 0; }
        close (cs.fd2);
	p = wd (p);
        cs = crw_deall (cs);
        return p;
}

crws crw_deall (crws cs) {
	free (cs.av_i);
	free (cs.av_i_d);
        free (cs.buf);
        free (cs.b);
        free (cs.oct);
        free (cs.z);
	return cs;
}

int deall_list (lln **head) {
	lln *current = *head;
	lln *next;
	while (current != NULL) {
		next = current->nx;
		free (current->nm);
		free (current);
		current = next;
	}
	*head = NULL;
	return 0;
}

ps deallocate (ps p) {
	free (p.o.l);
	free (p.o.s);
	free (p.z);
	free (p.buf);
	free (p.buf2);
	free (p.av_i_d);
	free (p.b);
	free (p.b2);
	deall_list (&(p.h));
	return p;
}

ps execute (ps p) {
       	if ( p.o.s[1] == 1 ) {
		if ((p.er = nma (p.ac, 4)) != 2) p = c(p);
	} else if ( p.o.s[2] == 1 ) {
		if ((p.er = nma (p.ac, 4)) != 2) p = r(p);
	} else if ( p.o.s[3] == 1 ) {
		p = t(p);
	} else if ( p.o.s[4] == 1 ) {
		if ((p.er = nma (p.ac, 4)) != 2) p = u(p);
	} else if ( p.o.s[5] == 1 ) {
		p = x(p);
	}
	return p;
}

ps fill_pos (ps p) {
        if (p.av[1][0] == '-') { p.o.s[0] = 1; }
        for (int i = 0; p.av[1][i] != '\0'; i++) {
        	for (int j = 1; j < 6; j++) {
         		if (p.av[1][i] == p.o.l[j]) {
         			p.o.s[j] = 1;
         			p.o.s[7] = 1;
         			p.oc++;
        		}
       		}
       	        if (p.av[1][i] == 'f') { p.o.s[6] = 1; }
       	}
	return p;
}

ps la (ps p) {
	int i = 0, j = 0;
	while (1) {
		j = 0;
		read(p.fd, p.buf, 100);
		i = my_strlen (p.buf);
		if ( i == 0 ) {	break; }
		p = push (p);
	        for (i = 0; i < 100; i++) { p.buf[i] = 0; }
		lseek(p.fd, 24, SEEK_CUR);
		read(p.fd, p.buf, 12);
	        for (i = 0; i < 12; i++) {
			j += (p.buf[i] - 48)*my_pow(8,10-i);
	        }
		lseek(p.fd, 20, SEEK_CUR);
		read(p.fd, p.buf, 1);
		if ( ( i = j % 512 ) ) j += 512 - i;
		if ( p.buf[0] == '5' ) j = 0;
		lseek(p.fd, 355 + j, SEEK_CUR);
	}
	p = print (p);
	return p;
}

int main (int argc, char **argv) {
	ps p;
	p.ac = argc;
	p.av = argv;
	p = allocate (p);
	p = check_args (p);
        if (p.er == 2) {
		p = deallocate (p);
		return 2;
	} else {
		p = execute (p);
		p = deallocate (p);
	}
	if (p.er == 2) return 2;
	return 0;
}

crws mogst (crws cs) {
	if ( cs.sw ) {	lstat (cs.av_i_d, cs.b);
	} else		lstat (cs.av_i  , cs.b);
	char *mugsta = "mugst";
	for (int i = 0; i < 5; i++) {
		cs.c = mugsta[i];
		cs = mugst (cs);
		cs = oct (cs);
		my_strcp (cs.oct, cs.buf, cs.i);
		cs.i += cs.k + 1;
		for (int j = 0; j < 12; j++) { cs.oct[j] = 0; }
	}
	return cs;
}

crws mugst (crws cs) {
	if (cs.c == 'm') {
		cs.j = cs.b->st_mode;
		cs.k = 7; }
	if (cs.c == 'u') {
		cs.j = cs.b->st_uid;
		cs.k = 7; }
	if (cs.c == 'g') {
		cs.j = cs.b->st_gid;
		cs.k = 7; }
	if (cs.c == 's') {
		cs.j = cs.b->st_size;
		cs.k = 11; }
	if (cs.c == 't') {
		cs.j = cs.b->st_mtime;
		cs.k = 11; }
	return cs;
}

int my_pow(int param_1, int param_2) {
        if (param_2 < 0) return 0;
        if (param_2 == 0) return 1;
        int i = 0, j = 1;
        for (i = 0; i != param_2; i++) {
                j = j * param_1;
        }
        return j;
}

int my_strcmp (char *a, char *b) {
	int i = 0;
        for (int i = 0; a[i] != '\0' || b[i] != '\0'; i++) {
                if ( a[i] > b[i] ) return 1;
                if ( a[i] < b[i] ) return 2;
        }
        if ( a[i] == '\0' ) return 2;
        if ( b[i] == '\0' ) return 1;
        return 0;
}

char *my_strcp (char *s1, char *s2, int j) {
	int i = 0;
	for ( i = 0; s1[ i ] != '\0'; i++ ) {
		s2[ j ] = s1[ i ];
		j++;
	}
	s2[ j ] = '\0';
	return s2;
}

int my_strlen(char* param_1) {
    int i = 0;
    while (param_1[i] != '\0')
    {
        i++;
    }
    return i;
}

int nma (int i, int j) {
	if (i < j) {
		write (2, "need more args\n", 15);
		return 2;
	}
	return 0;
}

bool nsf (char *filename) {
	struct stat buffer;
	return (lstat (filename, &buffer) != 0);
}

crws oct (crws cs) {
	char o[]= "01234567";
	int i = 0;
	while ( cs.j != 0) {
		cs.oct[ i ] = o [ cs.j % 8 ];
		cs.j = cs.j / 8;
		i++;
	}
	for (; cs.k - i != 0; i++) {
		cs.oct[ i ] = '0';
	}
	cs.oct[ i ] = '\0';
	reverse_string(cs.oct);
	if (cs.c == 'm') {
		for (i = 0; i < 4; i++) cs.oct[ i ] = '0';
	}
	return cs;
}

ps p_opt_er (ps p) {
	int i = my_strlen(p.av[1]);
	i -= p.o.s[0] + p.o.s[6] + p.o.s[7];
	if (p.o.s[7] == 0) {
		if (p.o.s[6] == 1) {
			write (2, "need options -crtux\n", 20);
			p.er = 2; return p;
		}
		write (2, "need options -crtuxf\n", 21);
		p.er = 2;
	} else if (p.o.s[6] == 0) {
			write (2, "need option -f\n", 15);
			p.er = 2;
	} else if (i > 0) {
			write (2, "too many options\n", 17);
			p.er = 2;
	}
	return p;
}

ps print (ps p) {
	p.h = rll(p.h);
	lln *temp;
	temp = p.h;
        int i = 0;
        while (temp != NULL) {
	        i = my_strlen (temp->nm);
                if (i) {
                	write(1, temp->nm, i);
			if (temp->nx) write(1, "\n", 1);
                }
                temp = temp->nx;
        }
	return p;
}

ps push (ps p) {
	lln *new_node = malloc(sizeof(lln));
	int i = my_strlen (p.buf) + 1;
	char *new_name = malloc(sizeof(char)*i);
	my_strcp (p.buf, new_name, 0);
	new_node->nm = new_name;
	new_node->ts = p.ts;
	new_node->nx = p.h;
	p.h = new_node;
	return p;
}

ps r (ps p) {
	if (cant(p.av[2])) {
		p.er = 2; return p;
	}
	p = c(p);
	return p;
}

char *reverse_string(char *s)
{
        char sw;
        int l = my_strlen(s);
        for (int i = 0; i < l / 2; i++){
                sw = s [ i ];
                s [ i ] = s [ l - i - 1 ];
                s [ l - i - 1 ] = sw;
        }
        return s;
}

lln* rll(lln* head_ref) {
        lln* a = NULL;
        lln* b = head_ref;
        lln* c = NULL;
        while (b != NULL) {
                c = b->nx;
                b->nx = a;
                a = b;
                b = c;
        }
        head_ref = a;
        return head_ref;
}

ps t (ps p) {
	if (p.ac > 3) {
		write (2, "too many args\n", 14);
		p.er = 2; return p;
	}
	if (cant(p.av[2])) {
		p.er = 2; return p;
	}
	p.fd = open (p.av[2], O_RDONLY);
	p = la (p);
        close (p.fd);
	return p;
}

int tc (ps p) {
	bool b = 0;
	stat (p.av_i, p.b2);
	lln *t = rll(p.h);
	while (t != NULL) {
		if (!my_strcmp(p.av_i, t->nm)){
			if( p.b2->st_mtime < t->ts) {
				b = 1;
				write (2, "file's old\n", 11);
			} else {
				b = 0;
			}
		}
		t = t->nx;
	}
	return b;
}

crws tf (crws cs) {
	if (S_ISREG(cs.b->st_mode)) my_strcp ("0", cs.buf, cs.i);
	if (S_ISLNK(cs.b->st_mode)) my_strcp ("2", cs.buf, cs.i);
	if (S_ISCHR(cs.b->st_mode)) my_strcp ("3", cs.buf, cs.i);
	if (S_ISBLK(cs.b->st_mode)) my_strcp ("4", cs.buf, cs.i);
	if (S_ISDIR(cs.b->st_mode)) my_strcp ("5", cs.buf, cs.i);
	if (S_ISFIFO(cs.b->st_mode)) my_strcp ("6", cs.buf, cs.i);

	if (cs.b->st_nlink>1) my_strcp ("1", cs.buf, cs.i);

	cs.i++;
	return cs;
}

ps tl (ps p) {
	int i = 0, j = 0;
	while (1) {
		read(p.fd, p.buf, 100);
		i = my_strlen (p.buf);
		if ( i == 0 ) {	break; }
		lseek(p.fd, 24, SEEK_CUR);
		read(p.fd, p.buf2, 12);
	        for (i = 0; i < 12; i++) {
			j += (p.buf2[i] - 48)*my_pow(8,10-i);
	        }
		if ( ( i = j % 512 ) ) j += 512 - i;
		read (p.fd, p.buf2, 12);
	        for (i = 0; i < 12; i++) {
			p.ts += (p.buf2[i] - 48)*my_pow(8,10-i);
	        }
		p = push (p);
	        for (i = 0; i < 100; i++) { p.buf[i] = 0; }
	        for (i = 0; i < 12; i++) { p.buf2[i] = 0; }
		lseek(p.fd, 364 + j, SEEK_CUR);
	}
	return p;
}

ps u (ps p) {
	if (cant(p.av[2])) {
		p.er = 2; return p;
	}
	p = c(p);
	return p;
}

crws ugname (crws cs) {
	struct passwd *pw = getpwuid(cs.b->st_uid);
	if ( pw != NULL ) {
		my_strcp (pw->pw_name, cs.buf, cs.i);
		cs.i += 32;
	}
	struct group  *gr = getgrgid(cs.b->st_gid);
	if ( gr != NULL ) {
		my_strcp (gr->gr_name, cs.buf, cs.i);
		cs.i += 32;
	}
	return cs;
}

crws wb (crws cs) {
	if (cs.buf[156] == '0') {
	        while (cs.bs > 0) {
	                cs.bs = read (cs.fd2, cs.buf, 512);
	                write (cs.fd, cs.buf, cs.bs);
	                if ( cs.bs > 0 && cs.bs < 512) {
	                        write (cs.fd, cs.z, 512 - cs.bs);
	                }
	        }
        }
        return cs;
}

ps wd (ps p) {
	if (S_ISDIR(p.b->st_mode) && !p.sw) {
		p.dp = opendir( p.av_i );
		while ( (p.dl = readdir(p.dp)) != 0 ) {
                	lstat(p.dl->d_name, p.b);
			if (p.dl->d_name[0] == '.') {
	                        continue;
                	}
			p.sw = 1;
			p = crw (p);
       		}
        	closedir (p.dp);
        	p.sw = 0;
	}
	return p;
}

crws wh (crws cs) {
	if ( cs.sw ) {	my_strcp (cs.av_i_d, cs.buf, 0);
	} else		my_strcp (cs.av_i,   cs.buf, 0);
	cs.i = 100;
	cs = mogst (cs);
	my_strcp ("        ", cs.buf, cs.i);
	cs.i += 8;
	cs = tf (cs);
	cs.i += 100;
	my_strcp ("ustar  ", cs.buf, cs.i);
	cs.i += 8;
	cs = ugname (cs);
	cs = chksum (cs);
	return cs;
}

ps xa (ps p) {
	int i = 1;
	while (1) {
		read(p.fd, p.buf, 100);
		i = my_strlen (p.buf) + 1 ;
		if ( i == 1 ) { break; }
		p.s = malloc (sizeof(char) * i);
		my_strcp (p.buf, p.s, 0);
		p = xrw (p);
		free (p.s);
	}
	return p;
}

ps x (ps p) {
	if (p.ac > 3) {
		write (2, "too many args\n", 14);
		p.er = 2; return p;
	}
	if (cant(p.av[2])) {
		p.er = 2; return p;
	}
	p.fd = open (p.av[2], O_RDONLY);
	p = xa (p);
	close (p.fd);
	return p;
}

ps xrw (ps p) {
	int i = 1, j = 0, k = 0;
        for ( int l = 0; l < 100; l++) { p.buf[l] = 0; }
	read(p.fd, p.buf, 8);
        for (k = 3; k < 7; k++) {
		j += (p.buf[k] - 48) * my_pow(8, 6-k);
	}
 	i = open (p.s, O_CREAT|O_WRONLY|O_TRUNC, j);
        j = 0;
	lseek(p.fd, 16, SEEK_CUR);
	read(p.fd, p.buf, 12);
        for (k = 0; k < 12; k++) {
		j += (p.buf[k] - 48) * my_pow(8, 10-k);
        }
	lseek(p.fd, 376, SEEK_CUR);
	for (k = 0; k < (j-(j % 512))/512; k++) {
		read(p.fd, p.buf, 512);
		write (i, p.buf, 512);
	}
	read(p.fd, p.buf, j % 512);
	write (i, p.buf, j % 512);
	lseek(p.fd, 512-(j%512), SEEK_CUR);
	close (i);
	return p;
}
