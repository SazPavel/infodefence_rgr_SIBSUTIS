#include "graph.h"

int main(int argc, char *argv[])
{
    int i,*encrypted_vertexes, n, m, command, **A;
    int sock, vertexes_for_test[2], vertexes_for_test_encrypt[2], key[2], vertexes_for_test_num[2];
    int vertexes_for_test_server_decrypt[2], *server_key, *vertexes_decrypt, *vertexes_decrypt_2;
    struct sockaddr_in addr;
    char *end;
    char buf[2];
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("sock");
        exit(-1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3429);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    A = load_graph(&m, &n, "tmp/graph");
    encrypted_vertexes = malloc(n * sizeof(int));
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(-1);
    }
    while(1)
    {
        printf("1 - another one test, other - finish testing\n");
        do
        {
            if(!fgets(buf, sizeof(buf), stdin))
                break;
            command = strtol(buf, &end, 10);
        }while(end != buf + strlen(buf));   //reading an input line

        send(sock, &command, sizeof(int), 0);
        if(command != 1)
        {    
            break;
        }

        recv(sock, encrypted_vertexes, sizeof(int)*n, 0);
        generate_two_different_numbers(vertexes_for_test_num, n, A);
        printf("encrypted_vertexes:\n");
        for(i = 0; i < n; i++)
            printf("%d ", encrypted_vertexes[i]);
        printf("\n");
        for(i = 0; i < 2; i++)
            vertexes_for_test[i] = encrypted_vertexes[vertexes_for_test_num[i]];
        vernam_encrypt(2, vertexes_for_test, vertexes_for_test_encrypt, key);
        send(sock, vertexes_for_test_num, sizeof(int)*2, 0);
        send(sock, vertexes_for_test_encrypt, sizeof(int)*2, 0);
        recv(sock, vertexes_for_test_server_decrypt, sizeof(int)*2, 0);
        server_key = vernam_decrypt(2, vertexes_for_test_encrypt, vertexes_for_test_server_decrypt);
        vertexes_decrypt = vernam_decrypt(2, vertexes_for_test_server_decrypt, key);
        if(vertexes_decrypt[0] == vertexes_decrypt[1])
        {
            printf("ERROR vertex equal!\n");
        }
        vertexes_decrypt_2 = vernam_decrypt(2, vertexes_for_test, server_key);
        for(i = 0; i < 2; i++)
        {
            if(vertexes_decrypt_2[i] != vertexes_decrypt[i])
                printf("ERROR server key changed!\n");
        }
        printf("vertex %d: color %d\nvertex %d: color %d\n", vertexes_for_test_num[0], vertexes_decrypt[0]-1, vertexes_for_test_num[1], vertexes_decrypt[1]-1);
    }
    for(i = 0; i < n; i++)
        free(A[i]);
    free(A);
    free(encrypted_vertexes);
    close(sock);
    exit(0);
}
