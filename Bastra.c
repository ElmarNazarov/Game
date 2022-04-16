#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
int card_draw(int player_cards[13][52][2]);
int game(int player_cards[13][52][2], char typecard[4][100], char numcard[13][99], int row, int removed[2], int counter[4]);
int player(int player_cards[13][52][2], char typecard[4][100], char numcard[13][99], int row);
void rem(int player_cards[13][52][2], int row, int l, int removed[2]);
int perm(int player_cards[13][52][2], int i, int l, int size);
int del_count(int player_cards[13][52][2], int i, int l, int size, int removed[2], int k);
int fact(int n);
int counting(int player_cards[13][52][2], int size, int c, int row, int removed[2]);
int size(int row, int player_cards[row][52][2]);
void adding(int player_cards[13][52][2], int row, int b, int removed[2]);
int winner(int counter[4]);
void main()
{
    int player_cards[13][52][2], removed[2], counter[4], win;
    char typecard[4][100] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    char numcard[13][99] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    card_draw(player_cards);
    printf("\033c");
    for (int i = 0; i < 4; i++)
    {
        counter[i] = 0;
    }
    for (int i = 0; i < 12; i += 4)
    {
        while (size(i + 3, player_cards) != 0)
        {
            for (int l = i; l < i + 4; l++)
            {
                game(player_cards, typecard, numcard, l, removed, counter);
            }
        }
    }
    win = winner(counter);
    if (win == 13)
    {
        printf("\tTIE");
    }
    else
    {
        printf(" ||%d|| ||winner player is: %d|| \n", counter[win], win + 1);
    }
}
int card_draw(int player_cards[16][52][2])
{
    bool chek = true;
    srand(time(0));
    for (int i = 0; i < 13; i++)
    {
        for (int l = 0; l < 4; l++)
        {
            chek = true;
            player_cards[i][l][1] = (rand() % 4) + 1;
            player_cards[i][l][2] = (rand() % 13) + 1;
            player_cards[i][l + 1][1] = 0;
            for (int k = 0; k <= i; k++)
            {
                for (int n = 0; (k < i && n < 4) || (k == i && n < l); n++)
                {
                    if (player_cards[k][n][1] == player_cards[i][l][1] && player_cards[k][n][2] == player_cards[i][l][2])
                    {
                        chek = false;
                        break;
                    }
                }
                if (!chek)
                {
                    break;
                }
            }
            if (!chek)
            {
                l--;
                continue;
            }
        }
    }
}
int player(int player_cards[13][52][2], char typecard[4][100], char numcard[13][99], int row)

{
    int card = 10;
    printf(" %d ", size(12, player_cards));
    printf("CARDS ON THE TABLE ARE:\n");
    printf("=============================================================================================================================================\n");
    for (int i = 0; i < size(12, player_cards); i++)
    {
        printf(" < %s : %s > ", typecard[player_cards[12][i][1] - 1], numcard[player_cards[12][i][2] - 1]);
    }
    printf("\n=============================================================================================================================================\n");
    printf("\n|| This cards are for %dth player ||", (row % 4) + 1);
    getchar();
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("Your cards is:\n\t");
    for (int i = 0; i < size(row, player_cards); i++)
    {
        printf(" < %s : %s > ", typecard[player_cards[row][i][1] - 1], numcard[player_cards[row][i][2] - 1]);
    }
    printf("\n-------------------------------------------------------------------------------------------------\n");
    while ((card > size(row, player_cards)) || (card > size(row, player_cards)))
    {
        printf("Chose which card you would like to put on the table: ");
        scanf(" %d", &card);
    }
    return card;
}
int game(int player_cards[13][52][2], char typecard[4][100], char numcard[13][99], int row, int removed[2], int counter[4])
{
    int card = player(player_cards, typecard, numcard, row);
    int count = counting(player_cards, size(12, player_cards), card - 1, row, removed);
    rem(player_cards, row, card - 1, removed);
    if (count != 0)
    {
        counter[row % 4] += count;
    }
    else
    {
        adding(player_cards, 12, 2, removed);
    }
    printf("+%d\n|| Your score is %d ||\n", count, counter[row % 4]);
    getchar();
    printf("\nIf you ready press ENTER\n");
    getchar();
    printf("\033c");
    return count;
}
int counting(int player_cards[13][52][2], int size, int c, int row, int removed[2])
{
    int num = 0;
    for (int i = 1; i <= size; i++)
    {
        if (player_cards[row][c][2] > 10 || (player_cards[row][c][2] == 7 && player_cards[row][c][1] == 2))
        {
            for (int l = size - 1; l >= 0; l--)
            {
                if (player_cards[12][l][2] == player_cards[row][c][2] || player_cards[row][c][2] == 11 || (player_cards[row][c][2] == 7 && player_cards[row][c][1] == 2))
                {
                    num += i;
                    rem(player_cards, 12, l, removed);
                }
            }
            break;
        }
        else
        {
            for (int l = 0; l < (fact(size) / (fact(i) * fact(size - i))); l++)
            {
                if (perm(player_cards, i, l, size) == player_cards[row][c][2])
                {
                    del_count(player_cards, i, l, size, removed, 0);
                    printf("\n");
                    num += i;
                }
            }
        }
    }
    if (num == 0)
    {
        return num;
    }
    else
    {
        return num + 1;
    }
}
void rem(int player_cards[13][52][2], int row, int col, int removed[2])
{
    removed[0] = player_cards[row][col][1];
    removed[1] = player_cards[row][col][2];
    while (player_cards[row][col][1] != 0)
    {
        player_cards[row][col][1] = player_cards[row][col + 1][1];
        player_cards[row][col][2] = player_cards[row][col + 1][2];
        col++;
    }
}
int fact(int n)
{
    int fact = 1;
    if (n == 0)
    {
        fact = 1;
    }
    else
    {
        for (int x = 1; x <= n; x++)
            fact = fact * x;
    }
    return fact;
}
int perm(int player_cards[13][52][2], int i, int l, int size)
{
    if (i == 0)
    {
        return 0;
    }
    else
    {
        int c = 1;
        while (l < 0 || l >= size)
        {
            l -= size;
            c++;
            if (c >= size)
            {
                return 0;
            }
        }
        return player_cards[12][l][2] + perm(player_cards, i - 1, l + c, size);
    }
}
int del_count(int player_cards[13][52][2], int i, int l, int size, int removed[2], int k)
{
    if (i == 0)
    {
        return 0;
    }
    else
    {
        int c = 1;
        while (l < 0 || l >= size)
        {
            l -= size;
            c++;
            if (c >= size)
            {
                return 0;
            }
        }
        rem(player_cards, 12, l - k, removed);
        del_count(player_cards, i - 1, l + c, size, removed, k + 1);
    }
}
int size(int row, int player_cards[row][52][2])
{
    int i;
    for (i = 0; player_cards[row][i][1] != 0; i++);
    return i;
}
void adding(int player_cards[13][52][2], int row, int b, int removed[2])
{
    player_cards[row][size(row, player_cards) + 1][1] = 0;
    player_cards[row][size(row, player_cards)][1] = removed[0];
    player_cards[row][size(row, player_cards) - 1][2] = removed[1];
}
int winner(int counter[4])
{
    int l = 0;
    for (int i = 0; i < 4; i++)
    {
        if (counter[i] > l)
        {
            l = i;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if ((counter[l] == counter[i]) && (l != i))
        {
            return 13;
        }
    }

    return l;
}