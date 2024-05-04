#include "lib.h"


int add_Node(int nid, Node** blockchain) {
        Node* current = *blockchain;
    while (current != NULL) {
        if (current->nid == nid) {
            printf("nok: this node already exists\n");
            return 1;
        }
        current = current->next;
    }
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("nok: no more resources available on the computer\n");
        return 1;
    }
    newNode->nid = nid;
    newNode->blockList = NULL;
    newNode->next = NULL;
    if (*blockchain == NULL) {
        *blockchain = newNode;
    } else {
        Node* last = *blockchain;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }
    return 0;
}

int remove_Node(int nid, Node** blockchain) {
    Node* prev = NULL;
    Node* current = *blockchain;

    while (current != NULL) {
        if (current->nid == nid) {
            if (prev == NULL) {
                *blockchain = current->next;
            } else {
                prev->next = current->next;
            }
            Block* blockCurrent = current->blockList;
            while (blockCurrent != NULL) {
                Block* temp = blockCurrent;
                blockCurrent = blockCurrent->next;
                free(temp->bid);
                free(temp);
            }
            free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    printf("nok: node %d doesn't exist\n", nid);
    return 4;
}

char* my_Strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* new_str = malloc(len);
    if (new_str == NULL) {
        return NULL;
    }
    strcpy(new_str, str);
    return new_str;
}

int add_Block(char* bid, int nid, Node* blockchain) {
    Node* curr = blockchain;
    while (curr != NULL) {
        if (nid == curr->nid || nid == -1) {
            Block* newBlock = malloc(sizeof(Block));
            if (newBlock == NULL) {
                printf("nok: no more resources available on the computer\n");
                return 1;
            }
            newBlock->bid = my_Strdup(bid);
            newBlock->next = NULL;
            Block* blockList = curr->blockList;
            if (blockList == NULL) {
                curr->blockList = newBlock;
            } else {
                while (blockList->next != NULL) {
                    blockList = blockList->next;
                }
                blockList->next = newBlock;
            }
            return 0;
        }
        curr = curr->next;
    }
    printf("nok: node %d doesn't exist\n", nid);
    return 2;
}

int remove_Block(char* bid, Node* blockchain) {
    int removed = 0;
    Node* current = blockchain;
    while (current != NULL) {
        Block* block = current->blockList;
        Block* prevBlock = NULL;
        while (block != NULL) {
            if (strcmp(block->bid, bid) == 0) {
                if (prevBlock == NULL) {
                    current->blockList = block->next;
                } else {
                    prevBlock->next = block->next;
                }
                free(block->bid);
                free(block);
                removed = 1;
                break;
            }
            prevBlock = block;
            block = block->next;
        }
        current = current->next;
    }
    
    if (removed) {
        return 0;  
    } else {
        return 5; 
    }
}

void print_Nodes(Node* blockchain, int listBlocks) {
    Node* current = blockchain;
    while (current != NULL) {
        printf("%d", current->nid);
        if (listBlocks) {
            Block* blockCurrent = current->blockList;
            printf(": ");
            while (blockCurrent != NULL) {
                printf("%s ", blockCurrent->bid);
                blockCurrent = blockCurrent->next;
            }
        }
        printf("\n");
        current = current->next;
    }
}

Block* find_Block(char* bid, Node* node) {
    Block* current = node->blockList;
    while (current != NULL) {
        if (strcmp(current->bid, bid) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void sync_Nodes(Node* blockchain) {
    for (Node* node1 = blockchain; node1 != NULL; node1 = node1->next) {
        for (Node* node2 = node1->next; node2 != NULL; node2 = node2->next) {
            for (Block* block = node1->blockList; block != NULL; block = block->next) {
                if (find_Block(block->bid, node2) == NULL) {
                    add_Block(block->bid, node2->nid, blockchain);
                }
            }
            for (Block* block = node2->blockList; block != NULL; block = block->next) {
                if (find_Block(block->bid, node1) == NULL) {
                    add_Block(block->bid, node1->nid, blockchain);
                }
            }
        }
    }
}

Node* find_Node(int nid, Node* blockchain) {
    Node* current = blockchain;
    while (current != NULL) {
        if (current->nid == nid) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int block_Count(Block* blockList) {
    int count = 0;
    Block* current = blockList;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int read_Line(int fd, char* line, size_t size) {
    size_t i = 0;
    while (i < size) {
        int n = read(fd, &line[i], 1);
        if (n == -1) {
            return -1; 
        } else if (n == 0) {
            return i; 
        } else if (line[i] == '\n') {
            line[i] = '\0';
            return i + 1;
        }
        i++;
    }
    line[size - 1] = '\0';
    return size; 
}

void save_Blockchain(Node* blockchain) {
    int fd = open(BLOCKCHAIN_FILENAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        printf("No Backup Found: Starting New Blockchain\n");
        return;
    }
    
    Node* current = blockchain;
    while (current != NULL) {
        char line[100];
        int n = snprintf(line, sizeof(line), "%d %d\n", current->nid, block_Count(current->blockList));
        write(fd, line, n);
        Block* blockCurrent = current->blockList;
        while (blockCurrent != NULL) {
            n = snprintf(line, sizeof(line), "%s\n", blockCurrent->bid);
            write(fd, line, n);
            blockCurrent = blockCurrent->next;
        }
        current = current->next;
    }
    close(fd);
}

int compare_BlockLists(Block* blockList1, Block* blockList2) {
    Block *tmp1 = blockList1, *tmp2 = blockList2;

    while (tmp1 != NULL && tmp2 != NULL) {
        if (strcmp(tmp1->bid, tmp2->bid) != 0) {
            return 0;
        }
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }

    if (tmp1 != NULL || tmp2 != NULL) {
        return 0;
    }

    return 1;
}


Node* load_Blockchain() {
    int fd = open(BLOCKCHAIN_FILENAME, O_RDONLY);
    if (fd == -1) {
        printf("No Backup Found: Starting New Blockchain\n");
        return NULL;
    }
    if(fd){
        printf("Restoring From Backup\n");
    }else{
            printf("Starting new blockchain...\n");
    }
    Node* blockchain = NULL;
    sync_Nodes(blockchain);
    
    char line[100];
    while (read_Line(fd, line, sizeof(line))) {
        int nid, numBlocks;
        int n = sscanf(line, "%d %d", &nid, &numBlocks);
        if (n != 2) {
            fprintf(stderr, "Error parsing line: %s", line);
            close(fd);
            return NULL;
        }
        add_Node(nid, &blockchain);
        find_Node(nid, blockchain);

        for (int i = 0; i < numBlocks; i++) {
            if (!read_Line(fd, line, sizeof(line))) {
                fprintf(stderr, "Unexpected end of file\n");
                close(fd);
                return NULL;
            }
            add_Block(line, nid, blockchain);
        }
    }
    
    close(fd);
    return blockchain;
}

int count_Nodes(Node* blockchain) {
    int count = 0;
    Node* temp = blockchain;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

bool check_Sync_State(Node* blockchain) {
    if (blockchain == NULL || blockchain->next == NULL) {
        return true;
    }

    Node* temp = blockchain;
    Block* firstBlockList = temp->blockList;

    while (temp->next != NULL) {
        temp = temp->next;
        if (!compare_BlockLists(firstBlockList, temp->blockList)) {
            return false;
        }
    }

    return true;
}


void free_Nodes(Node* blockchain) {
    Node* temp;
    while (blockchain != NULL) {
        temp = blockchain;
        blockchain = blockchain->next;
        free(temp);
    }
}


void process_Add_Command(char* arg1, char* arg2, char* arg3, Node** blockchain) {
    int n = 0;
    if (arg1 == NULL || arg2 == NULL) {
        printf("nok: missing argument\n");
    } else if (strcmp(arg1, "node") == 0) {
        n++;
        int nid = atoi(arg2);
        if (add_Node(nid, blockchain) == 0) {
            printf("OK\n");
        }
    } else if (strcmp(arg1, "block") == 0) {
        if (arg3 == NULL) {
            printf("nok: missing argument\n");
        } else {
            int nid;
            if (strcmp(arg3, "*") == 0) {
                nid = -1;
            } else {
                nid = atoi(arg3);
            }
            if (add_Block(arg2, nid, *blockchain) == 0) {
                printf("OK\n");
            }
        }
    } else {
        printf("nok: invalid command\n");
    }
}

void process_Rm_Command(char* arg1, char* arg2, Node** blockchain) {
    if (arg1 == NULL || arg2 == NULL) {
        printf("nok: missing argument\n");
    } else if (strcmp(arg1, "node") == 0) {
        int nid = strcmp(arg2, "*") == 0 ? -1 : atoi(arg2);
        if (nid == -1) {
            while (*blockchain != NULL) {
                remove_Node((*blockchain)->nid, blockchain);
            }
            printf("OK\n");
        } else if (remove_Node(nid, blockchain) == 0) {
            printf("OK\n");
        }
    } else if (strcmp(arg1, "block") == 0) {
        if (remove_Block(arg2, *blockchain) == 0) {
            printf("OK\n");
        } else {
            printf("nok: block %s doesn't exist\n", arg2);
        }
    } else {
        printf("nok: invalid command\n");
    }
}

void process_Ls_Command(char* arg1, Node* blockchain) {
    int listBlocks = 0;
    if (arg1 != NULL && strcmp(arg1, "-l") == 0) {
        listBlocks = 1;
    }
    print_Nodes(blockchain, listBlocks);
}

void process_Sync_Command(Node* blockchain) {
    sync_Nodes(blockchain);
    printf("OK\n");
}

void my_Blockchain() {
    Node* blockchain = load_Blockchain();
    char input[100];
    while (1) {     
        int numNodes = count_Nodes(blockchain);
        char syncState = check_Sync_State(blockchain) ? 's' : '-';
        printf("[%c%d]> ", syncState, numNodes);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("nok: failed to read input\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0';

        char* command = strtok(input, " ");
        char* arg1 = strtok(NULL, " ");
        char* arg2 = strtok(NULL, " ");
        char* arg3 = strtok(NULL, " ");

        if (command == NULL) {
            continue;
        } else if (strcmp(command, "add") == 0) {
            process_Add_Command(arg1, arg2, arg3, &blockchain);
        } else if (strcmp(command, "rm") == 0) {
            process_Rm_Command(arg1, arg2, &blockchain);
        } else if (strcmp(command, "ls") == 0) {
            process_Ls_Command(arg1, blockchain);
        } else if (strcmp(command, "sync") == 0) {
            process_Sync_Command(blockchain);
        } else if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) {
            printf("Backing up blockchain...\n");
            break;
        } else {
            printf("nok: invalid command\n");
        }
    }

    save_Blockchain(blockchain);
    free_Nodes(blockchain);
}

int main() {

    my_Blockchain();

    return 0;
}
