
#include <iostream>

class ATabuleiro 
{
public:
    ATabuleiro()//Construtor - Irá iniciar a nossa classe com o tabuleiro vazio
    {
        for (int IndiceDaLinha = 0; IndiceDaLinha < 3; ++IndiceDaLinha)
        {
            for (int IndiceDaColuna = 0; IndiceDaColuna < 3; ++IndiceDaColuna) 
            {
                Board[IndiceDaLinha][IndiceDaColuna] = ' '; //Repare que são aspas simples as aspas duplas são para constante char e vamos popular o nosso tabuleiro com X
            }
        }

    }


//Vamos criar uma função que retorna o valor contido na Matriz do tabuleiro. Para isso ela precisa receber uma linha e uma coluna. 
char PegarValorDaCedula(int linha, int coluna) const
    {
    return Board[linha][coluna];

    }
//Vamos criar uma função que escreve na matriz, veja que agora não vamos declarar como constante porque vamos alterar o valor efetivamente.
void SetarValorDaCedula(int linha, int coluna, char ValorASerInserido)
{
    Board[linha][coluna] = ValorASerInserido;

}

//Para o jogo terminar o tabuleiro deve ser totalmente preenchido para verificar isso vamos usar uma função
bool EstaCheiro() const
{
    for (int IndiceDaLinha = 0; IndiceDaLinha < 3; ++IndiceDaLinha)
    {
        for (int IndiceDaColuna = 0; IndiceDaColuna < 3; ++IndiceDaColuna)
        {
            if (Board[IndiceDaLinha][IndiceDaColuna] == ' ') //Verifica se tem caracter vazio 
            {
                return false;
            }
        }
    
    }
    return true;
}


//Vamos usar um metodo para verificar se o tabuleiro está vazio é praticamente o oposto do metodo anterior. 
bool EstaVazio() const 
{

    for (int IndiceDaLinha = 0; IndiceDaLinha < 3; ++IndiceDaLinha)
    {
        for (int IndiceDaColuna = 0; IndiceDaColuna < 3; ++IndiceDaColuna)
        {
            if (Board[IndiceDaLinha][IndiceDaColuna] != ' ') //Verifica tem caracter diferente de vazio 
            {
                return false;
            }
        }

    }
    return true;

}



void Print() const // Imprimi na tela o tabuleiro 
{
    for (int IndiceDaLinha = 0; IndiceDaLinha < 3; ++IndiceDaLinha)
    {
        std::cout << "\t"; // ante de imprimir a linha ele vai dar a distancia de um TAB do canto da tela. 
        for (int IndiceDaColuna = 0; IndiceDaColuna < 3; ++IndiceDaColuna)
        {
            std::cout << Board[IndiceDaLinha][IndiceDaColuna];// Neste momento o tabuleiro ainda está vazio porque anteriormente colocamos vazio na matriz
            if (IndiceDaColuna < 2)
            {
                std::cout << " | ";
            }
        }
        std::cout<<std::endl;//Derruba a linha após preencher os itens da linha
        if (IndiceDaLinha < 2) // Coloca a divisão na linha somente se o indice da linha for menor que 2
        {
            std::cout << "\t---------" << std::endl;
        }
    
        
    }


    std::cout << std::endl;//Derruba a linha após terminar de imprimir o tabuleiro
}
   
    
    
char PegarValor(int linhas,int colunas) const
{


}

private:
    char Board[3][3];//variável do tipo char que é uma matriz com 3 linhas e 3 colunas
    
};
class AJogador // será uma interface 
{
public:
    virtual const char* PegarNome() = 0;
    //=0 significa que as classes que herdam essa função devem implementar essas funções
    virtual void FazerMovimento(const ATabuleiro* Board, int& Linha, int& Coluna) = 0; //& em int& significa uma referência, e não o endereço de memória da variável. Dessa forma, não se lida diretamente com ponteiros.
};
class AJogadorHumano : public AJogador // Isso significa que a classe AJogadorHumano está herdando a classe Ajogador e que deve implementar o PegarNome() e o FazerMovimento()
{
public:
   
    
    const char* PegarNome() override //override confere se o PegarNome está na classe pai, se não estiver ele irá gerar um erro de compilação 
    {
        
        return "Jogador";

    }
    

    void FazerMovimento(const ATabuleiro* Board, int& Linha, int& Coluna) override
    {
    
        int Input = LerAEntrada();
        Linha = 2 - (Input - 1) / 3;
        Coluna = (Input - 1) % 3;
    
    }


private:
    int LerAEntrada()
    {
        while (true)
        {
            std::cout << "Faça sua jogada, escolha um numero entre 1 e 9\n";
            int Input;
            std::cin >> Input;
            if (Input > 0 && Input < 10)
            {
                return Input;
            }
            else
            {
                std::cout << "Jogada Invalida, tente novamente\n";               
            }          
        
        }     


    }




};
class AJogadorIA : public AJogador
{
public:
    const char* PegarNome() override
    {
        return "Robozinho";
    }

    void FazerMovimento(const ATabuleiro* Board, int& Linha, int& Coluna)
    {

        for (int IndiceDaLinha = 0; IndiceDaLinha < 3; ++IndiceDaLinha)
        {
            for (int IndiceDaColuna = 0; IndiceDaColuna < 3; ++IndiceDaColuna)
            {
                if (Board->PegarValorDaCedula(IndiceDaLinha, IndiceDaColuna) == ' ')//Como não estamos dentro da classe ATabuleiro precisamos usar a função que criamos na classe
                {

                    Linha = IndiceDaLinha;
                    Coluna = IndiceDaColuna;
                    return;
                }
            }


        }
    }
    
};

class AlogicaDoJogo
{
public:
    //Enumerator, falicita a comunição com as classes externas e deixa as informações mais amigaveis, nada mais é que uma lista que pode ser indexada.
    //Outra vantagem é evitar erros de digitação em nosso codigo já que so podemos usar valores definidos dentro do enum e eles já aparecem no como opção quando estamos escrevendo o codigo.
    enum class PossiveisResultados
    {
        NaoAcabou,
        Player1Ganhou,
        Player2Ganhou,
        Empate
    };
    
    
    AlogicaDoJogo()//Construtur da classe
    {
        //como estamos usando o new nos ponteiros em algum momento teremos que deleta-los e isso é feito no destrutor da classe. 
        Player1 = new AJogadorHumano;
        Player2 = new AJogadorIA;
        //se eu quisesse dois jogadores Humanos ? 
        /*
        Player1 = new AJogadorHumano;
        Player2 = new AJogadorHumano;
        
        */
        

    }
    ~AlogicaDoJogo() //Destrutor da classe.
    {
        delete Player1;
        delete Player2;

    }
    
    bool ValidarMovimento(int LinhaMovimento, int ColunaMovimento, char Valor)
    {
        if (Tabuleiro.PegarValorDaCedula(LinhaMovimento, ColunaMovimento) == ' ')
        {
            Tabuleiro.SetarValorDaCedula(LinhaMovimento, ColunaMovimento, Valor);
            return true;
        }
        else
        {
            return false;
        }
    }
    
    //Função para auxiliar o CheckSeOJogoAcabou
    bool EUmaLinha(char A, char B, char C)
    {
        return A != ' ' && A == B && B == C;
        //A diferente de vazio e A identido a B e B identico a C ou seja
        // X X X ou O O O 

    }

    void SetGameOver()
    {
        bFimDoJogo = true;
        if (bTurnoDoJogador) // se o jogo acabar no turno do jogador 1 é pq ele ganhou
        {
            ResultadoFinal = PossiveisResultados::Player1Ganhou;
        }
        else
        {
            ResultadoFinal = PossiveisResultados::Player2Ganhou;
        }
        //std::cout << "Fui chamado";
    }


    void  checkSeOjogoAcabou()
    {
        //verificar as linhas tem 3 caracteres consecutivos 
        for (int RowIndex = 0; RowIndex < 3; ++RowIndex)
        {
            char col0 = Tabuleiro.PegarValorDaCedula(RowIndex, 0);
            char col1 = Tabuleiro.PegarValorDaCedula(RowIndex, 1);
            char col2 = Tabuleiro.PegarValorDaCedula(RowIndex, 2);
            if (EUmaLinha(col0, col1, col2))
            {                
                SetGameOver();
                
                return;  
                
            }
        }
        //Verifica as colunas 
        for (int ColumnIndex = 0; ColumnIndex < 3; ++ColumnIndex)
        {
            char lin0 = Tabuleiro.PegarValorDaCedula(0,ColumnIndex);
            char lin1 = Tabuleiro.PegarValorDaCedula(1,ColumnIndex);
            char lin2 = Tabuleiro.PegarValorDaCedula(2,ColumnIndex);
            if (EUmaLinha(lin0, lin1, lin2))
            {                
                SetGameOver();
                //std::cout << "Teste Coluna\n";
                return;
               
            }
        }
        //Verificar as diagonais
        char diag0 = Tabuleiro.PegarValorDaCedula(0, 0);
        char diag1 = Tabuleiro.PegarValorDaCedula(1, 1);
        char diag2 = Tabuleiro.PegarValorDaCedula(2, 2);
        if (EUmaLinha(diag0, diag1, diag2))
        {
            SetGameOver();
            //std::cout << "Teste D1\n";
            return;
            
        }
        //Não é necessário usar outras variáveis para a diagonal, se a diagonal anterior for correta ela já irá setar o gameover e irá retornar. 
        diag0 = Tabuleiro.PegarValorDaCedula(0, 2);
        diag1 = Tabuleiro.PegarValorDaCedula(1, 1);
        diag2 = Tabuleiro.PegarValorDaCedula(2, 0);
        if (EUmaLinha(diag0, diag1, diag2))
        {
            SetGameOver();
            //std::cout << "Teste D2\n";
            return;
           
        }
        if (Tabuleiro.EstaCheiro())
        {
            bFimDoJogo = true;
            ResultadoFinal = PossiveisResultados::Empate;
           // std::cout << "Tabuleiro Cheio\n";
            return;
            
        
        }


    }

    
    void ProximoMovimento()
    {   
        int Linha, Coluna;//O FazerMovimento devolve a linha e a coluna portanto temos que ter as variáveis para recebe-las
        if (bTurnoDoJogador)
        {
            Player1->FazerMovimento(&Tabuleiro, Linha, Coluna);
        }
        else
        {
            Player2->FazerMovimento(&Tabuleiro, Linha, Coluna);
        }

        bool bEvalido = ValidarMovimento(Linha, Coluna, bTurnoDoJogador ? 'X' : 'O');//bEvalido verdadeiro ou falso se o ValidarMovimento aceitar na posição que o jogar pretende efetuar o movimento a particularidade é o bTurnoDoJogador ? 'X' : 'O' - a intergação fala que se for true informará o X e se não for o jogador 1 será O

        if (bEvalido)
        {
            checkSeOjogoAcabou();
            bTurnoDoJogador = !bTurnoDoJogador; // Estou negando o valor do booleano assim eu inverto o valor dele, se for falso para a ser true e se for true passa a ser falso igual ao nó flip flop na blueprint.
        }
    }

    void ImprimirResultado()
    {
        switch (ResultadoFinal) 
        {
        
        case AlogicaDoJogo::PossiveisResultados::Player1Ganhou:
            std::cout << "O Vencedor é o " << Player1->PegarNome() << "\n";
            break;
        case AlogicaDoJogo::PossiveisResultados::Player2Ganhou:
            std::cout << "O Vencedor é o "<<Player2->PegarNome()<<"\n";
            break;
        case AlogicaDoJogo::PossiveisResultados::Empate:
            std::cout << "Jogo Empatado\n";
            break;
        default:
            break;
        }
        
    }


//Vamos chamar dois ponteiros para a classe base, com isso podemos configurar o nosso jogos para 2 humanos, 2 IA´s , Humano e IA pq estamos usando a classe Base.   
    AJogador* Player1;
    AJogador* Player2;

    //Os jogadores precisam de um tabuleiro para jogar
    ATabuleiro Tabuleiro;

    //Precisamos controlar se o jogo está no inicio ou no fim. 
    bool bFimDoJogo = false;

    //Controlar de quem é o turno ,ela é verdadeira pq o player 1 sempre começa.
    bool bTurnoDoJogador = true;

    //Definindo o ResultadoFinal do jogo
    //Resultado Final é um Enum que criamos, PossiveisResultado que no inicio armazena o vamor NaoAcabou.
    PossiveisResultados ResultadoFinal = PossiveisResultados::NaoAcabou;



};

void TesteJogadorIA()
    {
        AJogadorIA JogadorIA;
        ATabuleiro TabuleiroIA;

        int LinhaTesteIA, ColunaTesteIA;

        JogadorIA.FazerMovimento(&TabuleiroIA, LinhaTesteIA, ColunaTesteIA);
        std::cout << "Linha da IA: " << LinhaTesteIA << "\tColuna da IA: " << ColunaTesteIA << "\n";
    }
void TesteJogadoHumano()
{
   //Criando o nosso jogador e o tabuleiro em que ele ira jogar baseado nas classes que criamos, são variáveis que recebem a classe
    AJogadorHumano Player;
    ATabuleiro Tabuleiro;

    int LinhaTeste, ColunaTeste;

    //&Tabuleiro está chamando um ponteiro para tabuleiro 
    Player.FazerMovimento(&Tabuleiro, LinhaTeste, ColunaTeste);

    std::cout << "Linha: " << LinhaTeste << "\tColuna: " << ColunaTeste<<"\n";

}

int main()
    {
   //iniciando o nosso loop do jogo.
    AlogicaDoJogo Jogo;

    while (!Jogo.bFimDoJogo)//Enquanto o FimDoJogo não for verdadeiro
    {
        //Primeiro vamos mostrar o nosso tabuleiro, no primeiro momento estará vazio
        Jogo.Tabuleiro.Print();
        Jogo.ProximoMovimento();

    }
    Jogo.Tabuleiro.Print();
    Jogo.ImprimirResultado();
        return 0;
    }









