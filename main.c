#include <stdio.h>
#include <stdlib.h>
#include "functions.c"

void menu(int arquivoDeEntrada){
    system("clear || cls");
    printf("_____________________________\n");
    printf("        TESTES COVID         \n");
    printf("_____________________________\n");
    if(!arquivoDeEntrada)
        printf("1 - Cadastrar teste\n");
    printf("2 - Consultar teste\n");
    printf("3 - Cancelar teste\n");
    printf("4 - Salvar em arquivo\n");
    printf("5 - Visualizar testes\n");
    printf("6 - Relatorio\n");
    printf("0 - Sair\n");
    printf("_____________________________\n");
}

int main(int argc, char *argv[]){

    int opcao, tamanho = -1;
    teste *testes = NULL;
    int arquivoDeEntrada;

    // VERIFICA SE É PASSADO O ARGUMENTO DO ARQUIVO DE ENTRADA COM OS DADOS OU NAO
    if (argv[1] == NULL)
        arquivoDeEntrada = 0;
    else{
        arquivoDeEntrada = 1;
        testes = inserirDoArquivo(argv[1]);
        tamanho = pegar_tamanho(argv[1]);
    }

    do
    {
        menu(arquivoDeEntrada);
        printf("Digite a escolha:");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
                // ESTA OPCAO SO APARECE CASO NAO HAJA O ARGUMENTO DO ARQUIVO DE ENTRADA
                if(!arquivoDeEntrada){
                    printf("Quantos testes deseja cadastrar ? ");
                    scanf("%d", &tamanho);
                    testes = (teste*)malloc(tamanho*sizeof(teste));
                    cadastrar(testes, tamanho);
                }
                break;

            case 2:
                consultar(testes, tamanho);
                break;
            
            case 3:
                cancelar(testes, tamanho);
                break;

            case 4:
                salvar_arquivo(testes, tamanho);
                break;

            case 5:
                visualizar(testes, tamanho);
                break;

            case 6:
                relatorio(testes, tamanho);
                break;
            
            default:
                break;
        }

        system("pause");
    } while (opcao != 0);

    free(testes);
    return 0;
}