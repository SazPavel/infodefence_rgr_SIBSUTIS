#include "graph.h"

int main()
{
    int command, sock, child_sock, n, num_of_colors, *vertexes, *encrypted_vertexes, *key;
    int vertexes_for_test[2], vertexes_for_test_num[2], i;
    struct sockaddr_in addr, child;
    socklen_t size = sizeof(child);
    
    load_graph_size(&n, "tmp/graph");
    vertexes = load_colored(&num_of_colors, n, "tmp/graph2");   //array of vertex colors
    encrypted_vertexes = malloc(n * sizeof(int));
    key = malloc(n * sizeof(int));

    sock = socket(AF_INET, SOCK_STREAM, 0);     //tcp socket for communication
    if(sock < 0)
    {
        perror("socket");
        exit(-1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3423);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(-1);
    }
    listen(sock, 6);
    printf("f");
    child_sock = accept(sock, (struct sockaddr*)&child, &size);
    while(1)
    {  
        recv(child_sock, &command, sizeof(command), 0);
        if(command == 1)
        {
    printf("f");
            relabeling(n, num_of_colors, vertexes);
            printf("colors:\n");
            for(i = 0; i < n; i++)
                printf("%d ", vertexes[i]);
            printf("\n");
    printf("f");
            vernam_encrypt(n, vertexes, encrypted_vertexes, key);
            send(child_sock, encrypted_vertexes, sizeof(int)*n, 0);
            recv(child_sock, vertexes_for_test_num, sizeof(int)*2, 0);              //numbers of two vertexs for test
            recv(child_sock, vertexes_for_test, sizeof(int)*2, 0);                  //values of two vertexs for test
            vernam_part_decrypt(2, vertexes_for_test, vertexes_for_test_num, key);  //decrypt two vertexes for test
            send(child_sock, vertexes_for_test, sizeof(int)*2, 0);
        }else
            break;
    }
    free(vertexes);
    free(key);
    free(encrypted_vertexes);
    close(sock);
    exit(0);
}
