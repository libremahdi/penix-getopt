struct master_alw {
    char *name;
    unsigned int master_id;
};

struct master_avl {
    char *name;
    unsigned int master_id;
    unsigned int options_size;
    char **options;
};
