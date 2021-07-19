#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// STRUCT PARA ARMAZENAR A DATA DE NASCIMENTO
typedef struct sData{
    int dia;
    int mes;
    int ano;
}data;

// STRUCT GERAL DO TESTE
typedef struct sTest{
    int id;
    char nome[40];
    char cpf[11];
    data nascimento;
    char sexo;
    char bairro[30];
    char resultado;             //P ou N
    int idade;                  //CALCULADA A PARTIR DA DATA DE NASCIMENTO
    char valido[3];             //"SIM" OU "NAO"
}teste;

int pegar_idade(data nascimento){

    //PEGA A DATA ATUAL DA BIBLIOTECA TIME.H
    struct tm *data_atual;
    time_t segundos;
    time(&segundos);   
    data_atual = localtime(&segundos); 

    //CASO PESSOA JA TENHA FEITO ANIVERSARIO RETORNA: ANO ATUAL - ANO DE NASCIMENTO
    //CASO AINDA NAO TENHA FEITO DIMINUI 1
    if (data_atual->tm_mon > nascimento.mes)
        return (data_atual->tm_year+1900) - nascimento.ano;
    else if (data_atual->tm_mon < nascimento.mes)
        return (data_atual->tm_year+1899) - nascimento.ano;
    else if (data_atual->tm_mday >= nascimento.dia)
        return (data_atual->tm_year+1900) - nascimento.ano;
    else   
        return (data_atual->tm_year+1899) - nascimento.ano;
}

//PEGA AS INFOS DO USUARIO
teste pegar_teste(){
    teste t;
    // ============ NOME ==============
    fflush(stdin);
    printf("Digite o nome: ");
    gets(t.nome);
    // ============ CPF ==============
    fflush(stdin);
    printf("Digite o cpf (apenas numeros): ");
    gets(t.cpf);
    // ============ NASCIMENTO ==============
    printf("Digite o dia do nascimento: ");
    scanf("%d", &t.nascimento.dia);
    printf("Digite o mes do nascimento: ");
    scanf("%d", &t.nascimento.mes);
    printf("Digite o ano do nascimento: ");
    scanf("%d", &t.nascimento.ano);
    // ============ SEXO ==============
    fflush(stdin);
    printf("Digite o sexo (F/M): ");
    scanf("%c", &t.sexo);
    // ============ BAIRRO ==============
    fflush(stdin);
    printf("Digite o bairro: ");
    gets(t.bairro);
    // ============ RESULTADO ==============
    printf("Digite o resultado (P/N): ");
    scanf("%c", &t.resultado);
    // ============ IDADE ==============
    t.idade = pegar_idade(t.nascimento);
    // ============ VALIDO ==============
    strcpy(t.valido, "SIM");

    return t;
}

void cadastrar(teste *testes, int tamanho){

    int i;
    // ITERANDO SOBRE O NUMERO DE TESTES QUE SERÃO INSERIDOS E COLETANDO AS INFORMAÇÕES DOS USUARIOS
    for (i = 0; i < tamanho; i++)
    {
        testes[i] = pegar_teste();
        testes[i].id = i;
    }
 
}

void imprimir (teste t){
    printf("__________________________\n");
    printf("Teste %d\n", t.id);
    printf("--------------------------\n");
    printf("Nome: %s \n", t.nome);
    printf("CPF: %s \n", t.cpf);
    printf("Data Nascimento: %d/%d/%d \n", t.nascimento.dia, t.nascimento.mes, t.nascimento.ano);
    printf("Idade: %d anos \n", t.idade);
    printf("Sexo: %c \n", t.sexo);
    printf("Bairro: %s \n", t.bairro);
    if (t.resultado == 'P')
        printf("COVID-19: SIM \n");
    else
        printf("COVID-19: NAO \n");
    printf("Valido: %s \n", t.valido);

    printf("\n\n");

}

void consultar(teste *testes, int tamanho){
    //TAMANHO É INICIADO COM -1, CASO CONTINUE -1 É PORQUE AINDA NÃO HOUVE O CADASTRO DE TESTES
    if(tamanho == -1){
        printf("É necessario cadastrar testes primeiro\n");
        return;
    }

    char nome_procurado[20];
    int cont = 0;
    fflush(stdin);
    printf("Digite a pessoa a ser consultada: \n");
    gets(nome_procurado);

    int i;
    // ITERA SOBRE OS TESTES CADASTRADOS
    for (i = 0; i < tamanho; i++)
    {
        //SO IMPRIME CASO SEJA A PESSOA PROCURADA
        if (strcmp(nome_procurado, testes[i].nome) == 0){
            imprimir(testes[i]);
            cont++;
        }
    }
    
    // CASO NAO ENCONTRE NENHUM TESTES DO NOME PROCURADO
    if (cont == 0){
        printf("Essa pessoa ainda nao realizou testes! \n");
    }
}

void cancelar(teste *testes, int tamanho){

    int id_escolhido, i;
    char certeza;

    printf("Digite o numero do teste a ser excluido: ");
    scanf("%d", &id_escolhido);

    // VERIFICA SE É UM ID VALIDO
    if(id_escolhido > tamanho-1){
        printf("Id nao existente\n");
        return;
    }

    // ACHA O USUARIO COM O ID ESCOLHIDO
    for (i = 0; i < tamanho; i++)
    {
        if(testes[i].id == id_escolhido)
            break;
    }
    
    fflush(stdin);
    printf("Voce tem certeza que deseja cancelar o teste ? (s/n) ");
    scanf("%c", &certeza);

    if(certeza == 'n')
        return;
    else
        strcpy(testes[i].valido, "NAO");

}

void salvar_arquivo(teste *testes, int tamanho){

    char arquivo[20];
    int i;
    printf("Digite o nome do arquivo: ");
    fflush(stdin);
    gets(arquivo);

    // CONCATENA O NOME DO ARQUIVO COM A EXTENCAO .txt
    strcat(arquivo, ".txt");
    // ABRE O ARQUIVO PARA ESCRITA
    FILE *f = fopen(arquivo, "w");

    // GRAVA AS INFORMAÇÕES DE TODOS OS TESTES NO ARQUIVO
    for (i = 0; i < tamanho; i++)
    {
        fprintf(f, "__________________________\n");
        fprintf(f, "Teste %d\n", testes[i].id);
        fprintf(f,"--------------------------\n");
        fprintf(f,"Nome: %s \n", testes[i].nome);
        fprintf(f,"CPF: %s \n", testes[i].cpf);
        fprintf(f,"Data Nascimento: %d/%d/%d \n", testes[i].nascimento.dia, testes[i].nascimento.mes, testes[i].nascimento.ano);
        fprintf(f,"Idade: %d anos \n", testes[i].idade);
        fprintf(f,"Sexo: %c \n", testes[i].sexo);
        fprintf(f,"Bairro: %s \n", testes[i].bairro);
        if (testes[i].resultado == 'P')
            fprintf(f,"COVID-19: SIM \n");
        else
            fprintf(f,"COVID-19: NAO \n");
        fprintf(f,"Valido: %s \n", testes[i].valido);
    }
    
    fclose(f);
}

void visualizar(teste *testes, int tamanho){
    int i;
    for (i = 0; i < tamanho; i++)
    {
        imprimir(testes[i]);
    }
}

void relatorio(teste *testes, int tamanho){

    int i;
    float infectados = 0, naoInfectados = 0, jovensInfectados = 0, adultosInfectados = 0, idososInfectados = 0; 
    float porcInfectados, porcNaoInfectados, porcJovens, porcAdultos, porcIdosos;

    // PARA TODOS OS TESTES CADASTRADOS
    for (i = 0; i < tamanho; i++)
    {
        //SE FOI POSITIVO
        if (testes[i].resultado == 'P')
        {
            infectados++;                       //AUMENTA O NUMERO DE INFECTADOS
            if(testes[i].idade < 20)            //SE A PESSOA TEM MENOS DE 20 ANOS
                jovensInfectados++;             //AUMENTA O NUMERO DE JOVENS INFECTADOS
            else if (testes[i].idade < 60)      //MAIOR QUE 20 E MENOR QUE 60
                adultosInfectados++;            //AUMENTA O NUMERO DE ADULTOS INFECTADOS
            else                                //MAIOR QUE 60
                idososInfectados++;             //AUMENTA O NUMERO DE IDOSOS INFECTADOS
        }
    }

    //CALCULA AS PORCENTAGENS
    naoInfectados = tamanho - infectados;
    porcInfectados = (infectados / tamanho) * 100;
    porcNaoInfectados = (naoInfectados / tamanho) * 100;
    porcJovens = (jovensInfectados / infectados) * 100;
    porcAdultos = (adultosInfectados / infectados) * 100;
    porcIdosos = (idososInfectados / infectados) * 100;


    // IMPRIME O RELATORIO
    printf("__________________________\n");
    printf("RELATORIO COVID-19 \n");
    printf("--------------------------\n");
    printf("Numero de testes: %d \n", tamanho);
    printf("Pessoas nao infectadas: %.2f (%.2f) \n", naoInfectados, porcNaoInfectados);
    printf("Pessoas infectadas: %.2f (%.2f) \n", infectados, porcInfectados);
    printf("    Jovens infectados: %.2f (%.2f) \n", jovensInfectados, porcJovens);
    printf("    Adultos infectados: %.2f (%.2f) \n", adultosInfectados, porcAdultos);
    printf("    Idosos infectados: %.2f (%.2f) \n", idososInfectados, porcIdosos);
    printf("\n\n ");

}

teste* inserirDoArquivo(char *entrada){

    int numeroDeRegistros, i;
    teste *testes;
    char string1[40], string2[40], string3[40];
    int intInfo;
    char charInfo;

    // ABRE O ARQUIVO PASSADO COMO ARGUMENTO PARA LEITURA
    FILE *file = fopen(entrada, "r");

    // LE A PRIMEIRA LINHA PARA SABER O TAMANHO DA ALOCAÇÃO
    fscanf(file, "%d", &numeroDeRegistros);
    testes = (teste*)malloc(numeroDeRegistros*sizeof(teste));

    for (i = 0; i < numeroDeRegistros; i++)
    {
        testes[i].id = i;
        // ================== NOME =======================
        fscanf(file, "%s %s %s", string1, string2, string3);   //"Nome: Nome1 Sobrenome1" - lê cada string
        strcpy(string1, " ");                                  //FAÇO string1 ser um espaço
        strcat(string1, string3);                              //CONCATENO O PRIMEIRO NOME COM ESPAÇO
        strcpy(testes[i].nome, strcat(string2, string1));      //INSIRO NO REGISTRO A CONCATENAÇÃO COM O SOBRENOME

        // =================== CPF =======================
        fscanf(file, "%s %s", string1, string2);
        strcpy(testes[i].cpf, string2);

        // ================== NASCIMENTO =================
        fscanf(file, "%s %s %s", string1, string2, string3);   //"Data de nascimento:""
        fscanf(file, "%s %d", string1, &intInfo);              //"Dia: XX" - le o dia
        testes[i].nascimento.dia = intInfo;
        fscanf(file, "%s %d", string1, &intInfo);              //"Mes: XX" - le o mes
        testes[i].nascimento.mes = intInfo;
        fscanf(file, "%s %d", string1, &intInfo);              //"Ano: XXXX" - le o ano
        testes[i].nascimento.ano = intInfo;

        testes[i].idade = pegar_idade(testes[i].nascimento);   //CALCULO A IDADE

        // ===================== SEXO ====================
        fscanf(file, "%s %c", string1, &charInfo);
        testes[i].sexo = charInfo;

        // =================== BAIRRO ====================
        fscanf(file, "%s %s", string1, string2);
        strcpy(testes[i].bairro, string2); 

        // =================== RESULTADO =----------------
        fscanf(file, "%s %c", string1, &charInfo);
        //NA EXPLICAÇÃO DO PROBLEMA É TRATADO POSITIVO COMO 'P' POREM NO ARQUIVO DE ENTRADA DE EXEMPLO COMO 'S'
        if(charInfo == 'S')                     // CASO SEJA 'S' TRANSFORMO EM 'P'
            testes[i].resultado = 'P';
        else
            testes[i].resultado = charInfo;
    
        strcpy(testes[i].valido, "SIM");
        imprimir(testes[i]);
    }
    system("pause");
    fclose(file);

    return testes;
}

// LE APENAS A PRIMEIRA LINHA DO ARQUIVO PARA SETAR O TAMANHO CASO SEJA UTILIZADO O ARQUIVO DE ENTRADA
int pegar_tamanho(char *entrada){
    int tamanho;
    FILE *file = fopen(entrada, "r");
    fscanf(file, "%d", &tamanho);
    fclose(file);
    return tamanho;
}