#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include<curl/curl.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <time.h>
#include<stdbool.h>

#define SCREEN_WIDTH 1050
#define SCREEN_HEIGHT 700
#define GRID_SIZE 70
#define GRID_ROWS (SCREEN_HEIGHT / GRID_SIZE)
#define GRID_COLS (SCREEN_WIDTH / GRID_SIZE)
#define MAX_UNITS_PER_TILE 100

// internetten veri çekmek için struct tanımladık
struct MemoryStruct
{
    char *memory;
    size_t size;
};

// Yazma işlemi için geri çağırma fonksiyonu
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, struct MemoryStruct *userp)
{
    size_t realsize = size * nmemb; // Gerçek boyutu hesapla
    // Eğer memory NULL ise, malloc ile tahsis et
    if (userp->memory == NULL)
    {
        userp->memory = (char *)malloc(realsize + 1); // Başlangıçta bellek tahsis et
        if(userp->memory == NULL)
        {
            printf("Not enough memory!\n");
            return 0;
        }
    }
    else
    {
        // Bellek alanını genişlet
        char *new_memory = (char *)realloc(userp->memory, userp->size + realsize + 1);
        if(new_memory == NULL)
        {
            printf("Not enough memory!\n");
            return 0;
        }
        userp->memory = new_memory;
    }

    // Yeni verileri ekle
    memcpy(&(userp->memory[userp->size]), contents, realsize);
    userp->size += realsize;
    userp->memory[userp->size] = 0; // Sonlandırıcı karakter ekle
    return realsize;
}

void dizi_bosalt(char x[40])
{
    for(int a=0; a<40; a++)
    {
        //x[a]=" ";
    }
}

typedef struct
{
    char tarafi[30];
    char birlik_adi[30];
    double saldiri;
    double savunma;
    double saglik;
    double kritik_sans;
    int sayi;
} birlikler;

void degerleri_ata(birlikler *a,char taraf[20],char takim[10],char metin[1500])
{
    char *sonuc;
    strcpy(a->tarafi,taraf);

    sonuc = strstr(metin,taraf);
    sonuc = strstr(sonuc, takim);
    sonuc = strstr(sonuc, "saldiri");

    int y=0;

    while (isdigit(*(sonuc+y)) != 1)
    {
        y++;
        sonuc++;
    }
    char sayim[5];
    sonuc+=4;

    for (int x=0; x<5; x++)
    {
        sayim[x]=*(sonuc+x);
    }

    int sayi;

    sscanf(sayim, "%d",&sayi);

    strcpy(a->birlik_adi,takim);
    a->saldiri=sayi;

    sonuc = strstr(metin, taraf);
    sonuc = strstr(sonuc, takim);
    sonuc = strstr(sonuc, "savunma");

    y=0;

    while (isdigit(*(sonuc+y)) != 1)
    {
        y++;
        sonuc++;
    }
    sonuc+=4;
    char sayim2[5];


    for (int x=0; x<5; x++)
    {
        sayim2[x]=*(sonuc+x);
    }

    sscanf(sayim2, "%d",&sayi);

    a->savunma=sayi;

    sonuc = strstr(metin, taraf);
    sonuc = strstr(sonuc, takim);
    sonuc = strstr(sonuc, "saglik");

    y=0;

    while (isdigit(*(sonuc+y)) != 1)
    {
        y++;
        sonuc++;
    }
    sonuc+=4;
    char sayim3[5];


    for (int x=0; x<5; x++)
    {
        sayim3[x]=*(sonuc+x);
    }

    sscanf(sayim3, "%d",&sayi);

    a->saglik=sayi;

    sonuc = strstr(metin, taraf);
    sonuc = strstr(sonuc, takim);
    sonuc = strstr(sonuc, "kritik_sans");

    y=0;

    while (isdigit(*(sonuc+y)) != 1)
    {
        y++;
        sonuc++;
    }
    sonuc+=7;
    char sayim4[5];


    for (int x=0; x<5; x++)
    {
        sayim4[x]=*(sonuc+x);
    }

    sscanf(sayim4, "%d",&sayi);

    a->kritik_sans=sayi;
}

typedef struct
{
    char tarafi[30];
    char ad[20];
    char bonus_turu[30];
    int bonus_degeri;
    char etki[21];
} kahramanlar;

void kahraman_deger_ata(kahramanlar *a,char takim[20],char adi[20],char metin[3000])
{
    char *sonuc;

    strcpy(a->ad,adi);
    strcpy(a->tarafi,takim);

    sonuc = strstr(metin, takim);
    sonuc = strstr(sonuc, adi);
    sonuc = strstr(sonuc, "bonus_turu");
    sonuc = strchr(sonuc, ':');
    sonuc = strchr(sonuc, '"');
    sonuc++;
    char ozellik[20];

    for(int z=0; z<20; z++)
    {
        if(isalpha(*(sonuc+z)) !=0 || *(sonuc+z) == '_')
        {
            ozellik[z]=*(sonuc+z);
        }
    }
    strcpy(a->bonus_turu,ozellik);
    strcpy(ozellik,"              ");

    sonuc = strstr(metin, takim);
    sonuc = strstr(sonuc, adi);
    sonuc = strstr(sonuc, "bonus_degeri");
    sonuc = strchr(sonuc, ':');
    sonuc = strchr(sonuc, '"');
    sonuc++;
    char ozellik2[6];
    int sayi;
    for(int z=0; z<6; z++)
    {
        if(isdigit(*(sonuc+z)) !=0 )
        {
            ozellik2[z]=*(sonuc+z);
        }
    }
    sscanf(ozellik2,"%d",&sayi);
    a->bonus_degeri = sayi;

    sonuc = strstr(metin, takim);
    sonuc = strstr(sonuc, adi);
    sonuc = strstr(sonuc, "aciklama");
    sonuc = strchr(sonuc, ':');
    sonuc = strchr(sonuc, '"');
    sonuc++;
    char ozellik3[20];
    char etkim[20];

    for(int z=0; z<20; z++)
    {
        if((*sonuc+z) != ' ')
        {
            ozellik3[z]=*(sonuc+z);
        }
    }
    sscanf(ozellik3,"%s",etkim);
    strcpy(a->etki,etkim);
}

typedef struct
{
    char tarafi[30];
    char ad[20];
    char bonus_turu[30];
    int bonus_degeri;
    char etki[21];
} canavarlar;

void canavar_deger_ata(canavarlar *a,char takim[20],char adi[20],char metin[3000])
{
    char *sonuc;

    strcpy(a->ad,adi);
    strcpy(a->tarafi,takim);

    sonuc = strstr(metin, takim);
    sonuc = strstr(sonuc, adi);
    sonuc = strstr(sonuc, "etki_turu");
    sonuc = strchr(sonuc, ':');
    sonuc = strchr(sonuc, '"');
    sonuc++;
    char ozellik[20];

    for(int z=0; z<20; z++)
    {
        if(isalpha(*(sonuc+z)) !=0 || *(sonuc+z) == '_')
        {
            ozellik[z]=*(sonuc+z);
        }
    }
    strcpy(a->bonus_turu,ozellik);
    strcpy(ozellik,"              ");

    sonuc = strstr(metin, takim);
    sonuc = strstr(sonuc, adi);
    sonuc = strstr(sonuc, "etki_degeri");
    sonuc = strchr(sonuc, ':');
    sonuc = strchr(sonuc, '"');
    sonuc++;
    char ozellik2[6];
    int sayi;
    for(int z=0; z<6; z++)
    {
        if(isdigit(*(sonuc+z)) !=0 )
        {
            ozellik2[z]=*(sonuc+z);
        }
    }
    sscanf(ozellik2,"%d",&sayi);
    a->bonus_degeri = sayi;


    sonuc = strstr(metin, takim);
    sonuc = strstr(sonuc, adi);
    sonuc = strstr(sonuc, "aciklama");
    sonuc = strchr(sonuc, ':');
    sonuc = strchr(sonuc, '"');
    sonuc++;
    char ozellik3[20];
    char etkim[20];

    for(int z=0; z<20; z++)
    {
        if((*sonuc+z) != ' ')
        {
            ozellik3[z]=*(sonuc+z);
        }
    }
    sscanf(ozellik3,"%s",etkim);
    strcpy(a->etki,etkim);
}

struct arastirmalar
{
    char adi[20];
    int seviye1;
    int seviye2;
    int seviye3;
    char aciklama[50];
};

void arastirma_deger_ata(struct arastirmalar *a, const char *ad, const char *metin)
{
    strcpy(a->adi, ad);

    char *sonuc = strstr(metin, ad);
    if (sonuc != NULL)
    {
        sonuc = strstr(sonuc, "seviye_1");
        if (sonuc != NULL)
        {
            sonuc = strstr(sonuc, "deger");
            if (sonuc != NULL)
            {
                sonuc = strchr(sonuc, ':');
                if (sonuc != NULL)
                {
                    sonuc = strchr(sonuc, '"');
                    if (sonuc != NULL)
                    {
                        a->seviye1 = atoi(sonuc + 1);
                    }
                }
            }
        }
    }

    sonuc = strstr(metin, ad);
    if (sonuc != NULL)
    {
        sonuc = strstr(sonuc, "seviye_2");
        if (sonuc != NULL)
        {
            sonuc = strstr(sonuc, "deger");
            if (sonuc != NULL)
            {
                sonuc = strchr(sonuc, ':');
                if (sonuc != NULL)
                {
                    sonuc = strchr(sonuc, '"');
                    if (sonuc != NULL)
                    {
                        a->seviye2 = atoi(sonuc + 1);
                    }
                }
            }
        }
    }

    sonuc = strstr(metin, ad);
    if (sonuc != NULL)
    {
        sonuc = strstr(sonuc, "seviye_3");
        if (sonuc != NULL)
        {
            sonuc = strstr(sonuc, "deger");
            if (sonuc != NULL)
            {
                sonuc = strchr(sonuc, ':');
                if (sonuc != NULL)
                {
                    sonuc = strchr(sonuc, '"');
                    if (sonuc != NULL)
                    {
                        a->seviye3 = atoi(sonuc + 1);
                    }
                }
            }
        }
    }

    sonuc = strstr(metin, ad);
    if (sonuc != NULL)
    {
        sonuc = strstr(sonuc, "aciklama");
        if (sonuc != NULL)
        {
            sonuc = strchr(sonuc, ':');
            if (sonuc != NULL)
            {
                sonuc = strchr(sonuc, '"');
                if (sonuc != NULL)
                {
                    sonuc++;
                    int i = 0;
                    while (*sonuc != '"' && *sonuc != '\0' && i < 49)
                    {
                        a->aciklama[i] = *sonuc;
                        sonuc++;
                        i++;
                    }
                    a->aciklama[i] = '\0';
                }
            }
        }
    }
}

typedef struct
{
    char insan_kahramanlar[40];
    char insan_canavarlar[40];
    char insan_arastirmasi[30];
    int insan_arastirma_seviyesi;
    int okcular;
    int piyadeler;
    int suvariler;
    int kusatma_makineleri;

    char org_kahramanlar[40];
    char org_canavarlar[40];
    char org_arastirmasi[30];
    int org_arastirma_seviyesi;
    int troller;
    int varg_binicileri;
    int org_dovusculeri;
    int mizrakcilar;

} senaryo;

// ızgaradaki kareleri yapı olarak tanımlayıp değişkenleri içine ekliyoruz
struct Tile
{
    int unitCount;    // Birim sayısı
    int health;       // Sağlık değeri
    int characterIndex; // Karakter dizinini tut
};

// can barı çizme fonksiyonu yüzdeliğe göre renk değişir
void drawHealthBar(SDL_Renderer* renderer, int x, int y, int width, int height, int health, int maxHealth)
{
    SDL_Rect healthBarBack = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, 80, 3, 3, 255); //can barının boş kısmının rengi
    SDL_RenderFillRect(renderer, &healthBarBack);

    int healthWidth = (int)((float)health / maxHealth * width);

    // bar yüzdesine göre renkler
    float healthPercent = (float)health / maxHealth;
    if (healthPercent <= 0.20f)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // kırmızı
    }
    else if (healthPercent <= 0.70f)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // sarı
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 49, 156, 3, 255); // yeşil
    }

    SDL_Rect healthBarFront = { x, y, healthWidth, height };
    SDL_RenderFillRect(renderer, &healthBarFront);
}
// sdl_ttf ile birim sayısını yazdırma
void drawUnitCountOnTile(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, int unitCount, int x, int y)
{
    char unitCountText[4];
    snprintf(unitCountText, sizeof(unitCountText), "%d", unitCount);

    SDL_Surface* surface = TTF_RenderText_Solid(font, unitCountText, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_Rect textRect = { x+23 + GRID_SIZE / 2 - textWidth / 2, y-23 + GRID_SIZE / 2 - textHeight / 2, textWidth, textHeight };

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture);
}
// fotoğraf yüklemek için fonksiyon
SDL_Texture* loadPNGTexture(const char* filePath, SDL_Renderer* renderer)
{
    SDL_Surface* loadedSurface = IMG_Load(filePath);
    if (loadedSurface == NULL)
    {
        printf("Resim yuklenemedi! SDL_image Hatasi: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    return texture;
}
// simüle ediliyor yazısını ekranda gösteren fonksiyon
void displayText(SDL_Renderer* renderer, TTF_Font* font, const char* text)
{
    SDL_Color textColor = {0, 0, 0, 255};  // Siyah renk
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_Rect textRect;
    textRect.x = 270;
    textRect.y = 290;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}
// ızgara yapısını ayarlayan fonksiyon
void drawGrid(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Beyaz renk

    // yatay kısmı eşit parçalara bölme
    for (int i = 0; i <= GRID_ROWS; ++i)
    {
        SDL_RenderDrawLine(renderer, 0, i * GRID_SIZE, SCREEN_WIDTH, i * GRID_SIZE);
    }

    // dikey kısmı eşit parçalara bölme
    for (int j = 0; j <= GRID_COLS; ++j)
    {
        SDL_RenderDrawLine(renderer, j * GRID_SIZE, 0, j * GRID_SIZE, SCREEN_HEIGHT);
    }
}

int main(int argc, char* args[])
{
    //BIRLIKLER

    birlikler birliklerim[10];

    char *dosya_icerigi = (char *)malloc(1290 * sizeof(char));

    FILE *birliklerdosya;
    char ch;
    birliklerdosya = fopen("unit_types.json", "r");


    if (birliklerdosya == NULL)
    {
        printf("dosya acilamadi.\n");
        return 1;
    }

    int i=0;
    while ((ch = fgetc(birliklerdosya)) != EOF)
    {
        dosya_icerigi[i]=ch;
        i++;
    }

    degerleri_ata(&birliklerim[0],"insan_imparatorlugu","piyadeler",dosya_icerigi);
    degerleri_ata(&birliklerim[1],"insan_imparatorlugu","okcular",dosya_icerigi);
    degerleri_ata(&birliklerim[2],"insan_imparatorlugu","suvariler",dosya_icerigi);
    degerleri_ata(&birliklerim[3],"insan_imparatorlugu","kusatma_makineleri",dosya_icerigi);
    degerleri_ata(&birliklerim[4],"ork_legi","ork_dovusculeri",dosya_icerigi);
    degerleri_ata(&birliklerim[5],"ork_legi","mizrakcilar",dosya_icerigi);
    degerleri_ata(&birliklerim[6],"ork_legi","varg_binicileri",dosya_icerigi);
    degerleri_ata(&birliklerim[7],"ork_legi","troller",dosya_icerigi);

    fclose(birliklerdosya);
    free(dosya_icerigi);

    //KAHRAMANLAR

    kahramanlar kahraman[9];

    char *dosya_icerigi2 = (char *)malloc(1720 * sizeof(char));
    FILE *hero;
    char ch2;
    hero = fopen("heroes.json", "r");

    if (hero == NULL)
    {
        printf("dosya acilamadi.\n");
        return 1;
    }

    i=0;
    while ((ch2 = fgetc(hero)) != EOF)
    {
        dosya_icerigi2[i]=ch2;
        i++;
    }

    kahraman_deger_ata(&kahraman[0],"insan_imparatorlugu","Alparslan",dosya_icerigi2);
    kahraman_deger_ata(&kahraman[1],"insan_imparatorlugu","Fatih_Sultan_Mehmet",dosya_icerigi2);
    kahraman_deger_ata(&kahraman[2],"insan_imparatorlugu","Mete_Han",dosya_icerigi2);
    kahraman_deger_ata(&kahraman[3],"insan_imparatorlugu","Yavuz_Sultan_Selim",dosya_icerigi2);
    kahraman_deger_ata(&kahraman[4],"insan_imparatorlugu","Tugrul_Bey",dosya_icerigi2);
    kahraman_deger_ata(&kahraman[5],"ork_legi","Goruk_Vahsi",dosya_icerigi2);
    kahraman_deger_ata(&kahraman[6],"ork_legi","Thruk_Kemikkiran",dosya_icerigi2);
    kahraman_deger_ata(&kahraman[7],"ork_legi","Vrog_Kafakiran",dosya_icerigi2);
    kahraman_deger_ata(&kahraman[8],"ork_legi","Ugar_Zalim",dosya_icerigi2);

    fclose(hero);
    free(dosya_icerigi2);

    //CANAVAR

    canavarlar canavar[11];
    char ch3;

    char *dosya_icerigi3 = (char *)malloc(2030 * sizeof(char));
    FILE *canavardosya;
    canavardosya = fopen("creatures.json", "r");

    if (canavardosya == NULL)
    {
        printf("dosya acilamadi.\n");
        return 1;
    }

    i=0;
    while ((ch3 = fgetc(canavardosya)) != EOF)
    {
        dosya_icerigi3[i]=ch3;
        i++;
    }

    canavar_deger_ata(&canavar[0],"insan_imparatorlugu","Ejderha",dosya_icerigi3);
    canavar_deger_ata(&canavar[1],"insan_imparatorlugu","Agri_Dagi_Devleri",dosya_icerigi3);
    canavar_deger_ata(&canavar[2],"insan_imparatorlugu","Tepegoz",dosya_icerigi3);
    canavar_deger_ata(&canavar[3],"insan_imparatorlugu","Karakurt",dosya_icerigi3);
    canavar_deger_ata(&canavar[4],"insan_imparatorlugu","Samur",dosya_icerigi3);
    canavar_deger_ata(&canavar[5],"ork_legi","Kara_Troll",dosya_icerigi3);
    canavar_deger_ata(&canavar[6],"ork_legi","Golge_Kurtlari",dosya_icerigi3);
    canavar_deger_ata(&canavar[7],"ork_legi","Camur_Devleri",dosya_icerigi3);
    canavar_deger_ata(&canavar[8],"ork_legi","Ates_Iblisi",dosya_icerigi3);
    canavar_deger_ata(&canavar[9],"ork_legi","Makrog_Savas_Beyi",dosya_icerigi3);
    canavar_deger_ata(&canavar[10],"ork_legi","Buz_Devleri",dosya_icerigi3);

    fclose(canavardosya);
    free(dosya_icerigi3);

    // ARASTIRMALAR

    struct arastirmalar arastirma[4];

    char ch4;
    char *dosya_icerigi4 = (char *)malloc(1760 * sizeof(char));
    FILE *arastirmadosya;
    arastirmadosya = fopen("research.json", "r");

    if (arastirmadosya == NULL)
    {
        printf("dosya acilamadi.\n");
        return 1;
    }

    i = 0;
    while ((ch4 = fgetc(arastirmadosya)) != EOF)
    {
        dosya_icerigi4[i] = ch4;
        i++;
    }

    arastirma_deger_ata(&arastirma[0], "savunma_ustaligi", dosya_icerigi4);
    arastirma_deger_ata(&arastirma[1], "saldiri_gelistirmesi", dosya_icerigi4);
    arastirma_deger_ata(&arastirma[2], "elit_egitim", dosya_icerigi4);
    arastirma_deger_ata(&arastirma[3], "kusatma_ustaligi", dosya_icerigi4);

    fclose(arastirmadosya);
    free(dosya_icerigi4);

    // SENARYO

    senaryo senaryomuz;

    char ch5;

    char urller[10][60]=
    {
        "https://yapbenzet.org.tr/1.json",
        "https://yapbenzet.org.tr/2.json",
        "https://yapbenzet.org.tr/3.json",
        "https://yapbenzet.org.tr/4.json",
        "https://yapbenzet.org.tr/5.json",
        "https://yapbenzet.org.tr/6.json",
        "https://yapbenzet.org.tr/7.json",
        "https://yapbenzet.org.tr/8.json",
        "https://yapbenzet.org.tr/9.json",
        "https://yapbenzet.org.tr/10.json"
    };
    int secim;

    printf("1 ile 10 arasinda bir sayi giriniz : ");
    scanf("%d",&secim);

    if(secim > 10 || secim < 1)
    {
        printf("1 ile 10 arasinda bir sayi girmeliydiniz!");
        return 1;
    }

    CURL *curl; // curl pointerı
    CURLcode res; // curl fonksiyonunun dönüş değeri
    struct MemoryStruct chunk; // siteden aldığımız verileri tutan yapı

    chunk.memory = NULL; // en başta null olsun
    chunk.size = 0; // en başta sıfır olsun

    // cURL'ü başlat
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl)
    {
        // url yi dizi içinde bulup ayarla
        curl_easy_setopt(curl, CURLOPT_URL,urller[secim-1]);

        // geri dönüş fonksiyonunu ayarla
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

        // sitedeki verileri saklama alanını ayarla
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        // ssl doğrulamasını devre dışı bırak (yoksa açılmıyor)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // İsteği gerçekleştir
        res = curl_easy_perform(curl);

        // Hata kontrolü
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            // Başarıyla veriyi çektiğimizde, veriyi yazdır
            //printf("%s\n", chunk.memory);
        }
        // Temizleme
        curl_easy_cleanup(curl);
        // belleği boşalt
    }

    curl_global_cleanup(); // curl ü kapat

    char * sonuc;

    sonuc = strstr(chunk.memory,"insan_imparatorlugu");
    sonuc = strstr(sonuc,"kahramanlar");

    if(sonuc == NULL)
    {
        strcpy(senaryomuz.insan_kahramanlar," ");
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc = strchr(sonuc, '[');
        char ozellik[40];

        for(int z=0; z<40; z++)
        {
            ozellik[z]=*(sonuc+z);
            if(*(sonuc+z)== ']')
            {
                break;
            }
        }
        strcpy(senaryomuz.insan_kahramanlar,ozellik);
        dizi_bosalt(ozellik);
    }

    sonuc = strstr(chunk.memory,"insan_imparatorlugu");
    sonuc = strstr(sonuc,"canavarlar");
    if (sonuc == NULL)
    {
        strcpy(senaryomuz.insan_canavarlar," ");
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc = strchr(sonuc, '[');
        char ozellik2[40];

        for(int z=0; z<40; z++)
        {
            ozellik2[z]=*(sonuc+z);
            if(*(sonuc+z)== ']')
            {
                break;
            }
        }
        strcpy(senaryomuz.insan_canavarlar,ozellik2);
        dizi_bosalt(ozellik2);
    }

    sonuc = strstr(chunk.memory,"insan_imparatorlugu");
    sonuc = strstr(sonuc,"arastirma_seviyesi");
    sonuc = strchr(sonuc, ':');
    sonuc = strchr(sonuc, '"');
    sonuc++;
    char ozellik3[40];

    for(int z=0; z<40; z++)
    {

        if(*(sonuc+z)== '"')
        {
            break;
        }
        ozellik3[z]=*(sonuc+z);

    }
    strcpy(senaryomuz.insan_arastirmasi,ozellik3);

    dizi_bosalt(ozellik3);


    int sayi;
    sonuc = strstr(chunk.memory,"insan_imparatorlugu");
    sonuc = strstr(sonuc,"arastirma_seviyesi");
    sonuc = strchr(sonuc, ':');
    sonuc = strchr(sonuc, '"');
    sonuc++;
    sonuc = strchr(sonuc, '"');
    sonuc = strchr(sonuc, ':');
    sonuc++;

    sscanf(sonuc,"%d",&sayi);
    senaryomuz.insan_arastirma_seviyesi = sayi;


    sonuc = strstr(chunk.memory,"insan_imparatorlugu");
    sonuc = strstr(sonuc,"birimler");
    sonuc = strstr(sonuc,"okcular");

    if(sonuc == NULL)
    {
        senaryomuz.okcular = 0;
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc++;
        sscanf(sonuc,"%d",&sayi);
        senaryomuz.okcular = sayi;
    }

    sonuc = strstr(chunk.memory,"insan_imparatorlugu");
    sonuc = strstr(sonuc,"birimler");
    sonuc = strstr(sonuc,"piyadeler");

    if(sonuc == NULL)
    {
        senaryomuz.piyadeler = 0;
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc++;
        sscanf(sonuc,"%d",&sayi);
        senaryomuz.piyadeler = sayi;
    }

    sonuc = strstr(chunk.memory,"insan_imparatorlugu");
    sonuc = strstr(sonuc,"birimler");
    sonuc = strstr(sonuc,"kusatma_makineleri");

    if(sonuc == NULL)
    {
        senaryomuz.kusatma_makineleri = 0;
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc++;
        sscanf(sonuc,"%d",&sayi);
        senaryomuz.kusatma_makineleri = sayi;
    }

    sonuc = strstr(chunk.memory,"insan_imparatorlugu");
    sonuc = strstr(sonuc,"birimler");
    sonuc = strstr(sonuc,"suvariler");

    if(sonuc == NULL)
    {
        senaryomuz.suvariler = 0;
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc++;
        sscanf(sonuc,"%d",&sayi);
        senaryomuz.suvariler = sayi;
    }

    sonuc = strstr(chunk.memory,"ork_legi");
    sonuc = strstr(sonuc,"kahramanlar");
    if(sonuc == NULL)
    {
        strcpy(senaryomuz.org_kahramanlar," ");
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc = strchr(sonuc, '[');
        char ozellik4[40];

        for(int z=0; z<40; z++)
        {
            ozellik4[z]=*(sonuc+z);
            if(*(sonuc+z)== ']')
            {
                break;
            }
        }
        strcpy(senaryomuz.org_kahramanlar,ozellik4);
        dizi_bosalt(ozellik4);
    }

    sonuc = strstr(chunk.memory,"ork_legi");
    sonuc = strstr(sonuc,"canavarlar");
    if (sonuc == NULL)
    {
        strcpy(senaryomuz.org_canavarlar," ");
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc = strchr(sonuc, '[');
        char ozellik5[40];

        for(int z=0; z<40; z++)
        {
            ozellik5[z]=*(sonuc+z);
            if(*(sonuc+z)== ']')
            {
                break;
            }
        }
        strcpy(senaryomuz.org_canavarlar,ozellik5);
        dizi_bosalt(ozellik5);
    }

    sonuc = strstr(chunk.memory,"ork_legi");
    sonuc = strstr(sonuc,"arastirma_seviyesi");
    sonuc = strchr(sonuc, ':');
    sonuc = strchr(sonuc, '"');
    sonuc++;
    char ozellik6[40];

    for(int z=0; z<40; z++)
    {

        if(*(sonuc+z)== '"')
        {
            break;
        }
        ozellik6[z]=*(sonuc+z);

    }
    strcpy(senaryomuz.org_arastirmasi,ozellik6);
    dizi_bosalt(ozellik6);

    sonuc = strstr(chunk.memory,"ork_legi");
    sonuc = strstr(sonuc,"arastirma_seviyesi");
    sonuc = strchr(sonuc, ':');
    sonuc = strchr(sonuc, '"');
    sonuc++;
    sonuc = strchr(sonuc, '"');
    sonuc = strchr(sonuc, ':');
    sonuc++;

    sscanf(sonuc,"%d",&sayi);
    senaryomuz.org_arastirma_seviyesi = sayi;

    sonuc = strstr(chunk.memory,"ork_legi");
    sonuc = strstr(sonuc,"birimler");
    sonuc = strstr(sonuc,"mizrakcilar");

    if(sonuc == NULL)
    {
        senaryomuz.mizrakcilar = 0;
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc++;
        sscanf(sonuc,"%d",&sayi);
        senaryomuz.mizrakcilar = sayi;
    }

    sonuc = strstr(chunk.memory,"ork_legi");
    sonuc = strstr(sonuc,"birimler");
    sonuc = strstr(sonuc,"ork_dovusculeri");

    if(sonuc == NULL)
    {
        senaryomuz.org_dovusculeri = 0;
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc++;
        sscanf(sonuc,"%d",&sayi);
        senaryomuz.org_dovusculeri = sayi;
    }

    sonuc = strstr(chunk.memory,"ork_legi");
    sonuc = strstr(sonuc,"birimler");
    sonuc = strstr(sonuc,"troller");

    if(sonuc == NULL)
    {
        senaryomuz.troller = 0;
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc++;
        sscanf(sonuc,"%d",&sayi);
        senaryomuz.troller = sayi;
    }

    sonuc = strstr(chunk.memory,"ork_legi");
    sonuc = strstr(sonuc,"birimler");
    sonuc = strstr(sonuc,"varg_binicileri");

    if(sonuc == NULL)
    {
        senaryomuz.varg_binicileri = 0;
    }
    else
    {
        sonuc = strchr(sonuc, ':');
        sonuc++;
        sscanf(sonuc,"%d",&sayi);
        senaryomuz.varg_binicileri = sayi;
    }

    free(chunk.memory);

    //Saldiri ve Savunma guclerinin hesaplanmasi

    void guncelleme_yap()
    {
        //insan canavar deger guncelleme
        for(int i=0; i<11; i++)
        {
            if( strstr(senaryomuz.insan_canavarlar,canavar[i].ad) != NULL )
            {
                if ( strstr(canavar[i].bonus_turu,"saldiri")  != NULL )
                {
                    if ( strstr(canavar[i].etki,"okcular") != NULL)
                    {
                        birliklerim[1].saldiri += birliklerim[1].saldiri*canavar[i].bonus_degeri/100;
                    }
                    if ( strstr(canavar[i].etki,"piyade") != NULL)
                    {
                        birliklerim[0].saldiri += birliklerim[0].saldiri*canavar[i].bonus_degeri/100;
                    }
                    if ( strstr(canavar[i].etki,"suvari") != NULL)
                    {
                        birliklerim[2].saldiri += birliklerim[2].saldiri*canavar[i].bonus_degeri/100;
                    }
                    if ( strstr(canavar[i].etki,"kusatma") != NULL)
                    {
                        birliklerim[3].saldiri += birliklerim[3].saldiri*canavar[i].bonus_degeri/100;
                    }
                }
                if ( strstr(canavar[i].bonus_turu,"savunma") != NULL )
                {
                    if (strstr(canavar[i].etki, "okcular") != NULL)
                    {
                        birliklerim[1].savunma += birliklerim[1].savunma * canavar[i].bonus_degeri / 100;
                    }
                    if (strstr(canavar[i].etki, "piyade") != NULL)
                    {
                        birliklerim[0].savunma += birliklerim[0].savunma * canavar[i].bonus_degeri / 100;
                    }
                    if (strstr(canavar[i].etki, "suvari") != NULL)
                    {
                        birliklerim[2].savunma += birliklerim[2].savunma * canavar[i].bonus_degeri / 100;
                    }
                    if (strstr(canavar[i].etki, "kusatma") != NULL)
                    {
                        birliklerim[3].savunma += birliklerim[3].savunma * canavar[i].bonus_degeri / 100;
                    }
                }
                if ( strstr(canavar[i].bonus_turu,"kritik_sans") != NULL )
                {
                    if (strstr(canavar[i].etki, "okcular") != NULL)
                    {
                        birliklerim[1].kritik_sans += birliklerim[1].kritik_sans * canavar[i].bonus_degeri/100;
                    }
                    if (strstr(canavar[i].etki, "piyade") != NULL)
                    {
                        birliklerim[0].kritik_sans += birliklerim[0].kritik_sans * canavar[i].bonus_degeri/100;
                    }
                    if (strstr(canavar[i].etki, "suvari") != NULL)
                    {
                        birliklerim[2].kritik_sans += birliklerim[2].kritik_sans * canavar[i].bonus_degeri/100 ;
                    }
                    if (strstr(canavar[i].etki, "kusatma") != NULL)
                    {
                        birliklerim[3].kritik_sans += birliklerim[3].kritik_sans * canavar[i].bonus_degeri/100;
                    }
                }
            }
        }

        // insan arastirma deger guncelle

        for(int i=0; i<4; i++)
        {
            if(senaryomuz.insan_arastirmasi[3] == arastirma[i].adi[3])
            {
                if( strstr(arastirma[i].adi,"kusatma") != NULL)
                {
                    if(senaryomuz.insan_arastirma_seviyesi == 1)
                    {
                        birliklerim[3].saldiri += birliklerim[3].saldiri * arastirma[i].seviye1/100;
                    }
                    if(senaryomuz.insan_arastirma_seviyesi == 2)
                    {
                        birliklerim[3].saldiri += birliklerim[3].saldiri * arastirma[i].seviye2/100;
                    }
                    if(senaryomuz.insan_arastirma_seviyesi == 3)
                    {
                        birliklerim[3].saldiri += birliklerim[3].saldiri * arastirma[i].seviye3/100;
                    }
                }
                if( strstr(arastirma[i].adi,"elit") != NULL)
                {
                    if(senaryomuz.insan_arastirma_seviyesi == 1)
                    {
                        birliklerim[0].kritik_sans +=  birliklerim[0].kritik_sans * arastirma[i].seviye1/100;
                        birliklerim[1].kritik_sans +=  birliklerim[1].kritik_sans * arastirma[i].seviye1/100;
                        birliklerim[2].kritik_sans +=  birliklerim[2].kritik_sans * arastirma[i].seviye1/100;
                        birliklerim[3].kritik_sans +=  birliklerim[3].kritik_sans * arastirma[i].seviye1/100;
                    }
                    if(senaryomuz.insan_arastirma_seviyesi == 2)
                    {
                        birliklerim[0].kritik_sans += birliklerim[0].kritik_sans * arastirma[i].seviye2/100;
                        birliklerim[1].kritik_sans += birliklerim[1].kritik_sans * arastirma[i].seviye2/100;
                        birliklerim[2].kritik_sans += birliklerim[2].kritik_sans * arastirma[i].seviye2/100;
                        birliklerim[3].kritik_sans += birliklerim[3].kritik_sans * arastirma[i].seviye2/100;
                    }
                    if(senaryomuz.insan_arastirma_seviyesi == 3)
                    {
                        birliklerim[0].kritik_sans += birliklerim[0].kritik_sans * arastirma[i].seviye3/100;
                        birliklerim[1].kritik_sans += birliklerim[1].kritik_sans * arastirma[i].seviye3/100;
                        birliklerim[2].kritik_sans += birliklerim[2].kritik_sans * arastirma[i].seviye3/100;
                        birliklerim[3].kritik_sans += birliklerim[3].kritik_sans * arastirma[i].seviye3/100;
                    }
                }
                if( strstr(arastirma[i].adi,"sal") != NULL)
                {
                    if(senaryomuz.insan_arastirma_seviyesi == 1)
                    {
                        birliklerim[0].saldiri += birliklerim[0].saldiri * arastirma[i].seviye1/100;
                        birliklerim[1].saldiri += birliklerim[1].saldiri * arastirma[i].seviye1/100;
                        birliklerim[2].saldiri += birliklerim[2].saldiri * arastirma[i].seviye1/100;
                        birliklerim[3].saldiri += birliklerim[3].saldiri * arastirma[i].seviye1/100;
                    }
                    if(senaryomuz.insan_arastirma_seviyesi == 2)
                    {
                        birliklerim[0].saldiri += birliklerim[0].saldiri * arastirma[i].seviye2/100;
                        birliklerim[1].saldiri += birliklerim[1].saldiri * arastirma[i].seviye2/100;
                        birliklerim[2].saldiri += birliklerim[2].saldiri * arastirma[i].seviye2/100;
                        birliklerim[3].saldiri += birliklerim[3].saldiri * arastirma[i].seviye2/100;
                    }
                    if(senaryomuz.insan_arastirma_seviyesi == 3)
                    {
                        birliklerim[0].saldiri += birliklerim[0].saldiri * arastirma[i].seviye3/100;
                        birliklerim[1].saldiri += birliklerim[1].saldiri * arastirma[i].seviye3/100;
                        birliklerim[2].saldiri += birliklerim[2].saldiri * arastirma[i].seviye3/100;
                        birliklerim[3].saldiri += birliklerim[3].saldiri * arastirma[i].seviye3/100;
                    }
                }
                if (strstr(arastirma[i].adi, "savunma_ustaligi") != NULL)
                {
                    if (senaryomuz.insan_arastirma_seviyesi == 1)
                    {
                        birliklerim[0].savunma += birliklerim[0].savunma * arastirma[i].seviye1 / 100;
                        birliklerim[1].savunma += birliklerim[1].savunma * arastirma[i].seviye1 / 100;
                        birliklerim[2].savunma += birliklerim[2].savunma * arastirma[i].seviye1 / 100;
                        birliklerim[3].savunma += birliklerim[3].savunma * arastirma[i].seviye1 / 100;
                    }
                    if (senaryomuz.insan_arastirma_seviyesi == 2)
                    {
                        birliklerim[0].savunma += birliklerim[0].savunma * arastirma[i].seviye2 / 100;
                        birliklerim[1].savunma += birliklerim[1].savunma * arastirma[i].seviye2 / 100;
                        birliklerim[2].savunma += birliklerim[2].savunma * arastirma[i].seviye2 / 100;
                        birliklerim[3].savunma += birliklerim[3].savunma * arastirma[i].seviye2 / 100;
                    }
                    if (senaryomuz.insan_arastirma_seviyesi == 3)
                    {
                        birliklerim[0].savunma += birliklerim[0].savunma * arastirma[i].seviye3 / 100;
                        birliklerim[1].savunma += birliklerim[1].savunma * arastirma[i].seviye3 / 100;
                        birliklerim[2].savunma += birliklerim[2].savunma * arastirma[i].seviye3 / 100;
                        birliklerim[3].savunma += birliklerim[3].savunma * arastirma[i].seviye3 / 100;
                    }
                }
            }
        }

        //insan kahraman deger guncelle

        for(int i=0; i<9; i++)
        {
            if (strstr(senaryomuz.insan_kahramanlar, kahraman[i].ad) != NULL)
            {
                if (strstr(kahraman[i].bonus_turu, "saldiri") != NULL)
                {
                    if (strstr(kahraman[i].etki, "okcular") != NULL)
                    {
                        birliklerim[1].saldiri += birliklerim[1].saldiri * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "piyade") != NULL)
                    {
                        birliklerim[0].saldiri += birliklerim[0].saldiri * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "suvari") != NULL)
                    {
                        birliklerim[2].saldiri += birliklerim[2].saldiri * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "kusatma") != NULL)
                    {
                        birliklerim[3].saldiri += birliklerim[3].saldiri * kahraman[i].bonus_degeri / 100;
                    }
                }
                if (strstr(kahraman[i].bonus_turu, "savunma") != NULL)
                {
                    if (strstr(kahraman[i].etki, "okcular") != NULL)
                    {
                        birliklerim[1].savunma += birliklerim[1].savunma * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "piyade") != NULL)
                    {
                        birliklerim[0].savunma += birliklerim[0].savunma * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "suvari") != NULL)
                    {
                        birliklerim[2].savunma += birliklerim[2].savunma * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "kusatma") != NULL)
                    {
                        birliklerim[3].savunma += birliklerim[3].savunma * kahraman[i].bonus_degeri / 100;
                    }
                }
                if (strstr(kahraman[i].bonus_turu, "kritik_sans") != NULL)
                {
                    if (strstr(kahraman[i].etki, "okcular") != NULL)
                    {
                        birliklerim[1].kritik_sans += birliklerim[1].kritik_sans * kahraman[i].bonus_degeri/100;
                    }
                    if (strstr(kahraman[i].etki, "piyade") != NULL)
                    {
                        birliklerim[0].kritik_sans += birliklerim[0].kritik_sans * kahraman[i].bonus_degeri/100;
                    }
                    if (strstr(kahraman[i].etki, "suvari") != NULL)
                    {
                        birliklerim[2].kritik_sans += birliklerim[2].kritik_sans * kahraman[i].bonus_degeri/100;
                    }
                    if (strstr(kahraman[i].etki, "kusatma") != NULL)
                    {
                        birliklerim[3].kritik_sans += birliklerim[3].kritik_sans * kahraman[i].bonus_degeri/100;
                    }
                }
            }
        }

        double ork_saldiri_gucu = birliklerim[4].saldiri * senaryomuz.piyadeler + birliklerim[5].saldiri * senaryomuz.okcular + birliklerim[6].saldiri * senaryomuz.suvariler + birliklerim[7].saldiri * senaryomuz.kusatma_makineleri ;

        //ORKLAR

        //ork canavar deger guncelleme
        for(int i=0; i<11; i++)
        {
            if( strstr(senaryomuz.org_canavarlar,canavar[i].ad) != NULL )
            {
                if ( strstr(canavar[i].bonus_turu,"saldiri")  != NULL )
                {
                    if ( strstr(canavar[i].etki,"ork_dovusculeri") != NULL)
                    {
                        birliklerim[4].saldiri += birliklerim[4].saldiri*canavar[i].bonus_degeri/100;
                    }
                    if ( strstr(canavar[i].etki,"mizrakci") != NULL)
                    {
                        birliklerim[5].saldiri += birliklerim[5].saldiri*canavar[i].bonus_degeri/100;
                    }
                    if ( strstr(canavar[i].etki,"varg") != NULL)
                    {
                        birliklerim[6].saldiri += birliklerim[6].saldiri*canavar[i].bonus_degeri/100;
                    }
                    if ( strstr(canavar[i].etki,"trol") != NULL)
                    {
                        birliklerim[7].saldiri += birliklerim[7].saldiri*canavar[i].bonus_degeri/100;
                    }
                }
                if ( strstr(canavar[i].bonus_turu,"savunma") != NULL )
                {
                    if (strstr(canavar[i].etki, "ork_dovuscu") != NULL)
                    {
                        birliklerim[4].savunma += birliklerim[4].savunma * canavar[i].bonus_degeri / 100;
                    }
                    if (strstr(canavar[i].etki, "mizrakci") != NULL)
                    {
                        birliklerim[5].savunma += birliklerim[5].savunma * canavar[i].bonus_degeri / 100;
                    }
                    if (strstr(canavar[i].etki, "varg") != NULL)
                    {
                        birliklerim[6].savunma += birliklerim[6].savunma * canavar[i].bonus_degeri / 100;
                    }
                    if (strstr(canavar[i].etki, "trol") != NULL)
                    {
                        birliklerim[7].savunma += birliklerim[7].savunma * canavar[i].bonus_degeri / 100;
                    }
                }
                if ( strstr(canavar[i].bonus_turu,"kritik_sans") != NULL )
                {
                    if (strstr(canavar[i].etki, "ork_dovus") != NULL)
                    {
                        birliklerim[4].kritik_sans += birliklerim[4].kritik_sans * canavar[i].bonus_degeri/100;
                    }
                    if (strstr(canavar[i].etki, "mizrakci") != NULL)
                    {
                        birliklerim[5].kritik_sans += birliklerim[5].kritik_sans * canavar[i].bonus_degeri/100;
                    }
                    if (strstr(canavar[i].etki, "varg") != NULL)
                    {
                        birliklerim[6].kritik_sans += birliklerim[6].kritik_sans * canavar[i].bonus_degeri/100 ;
                    }
                    if (strstr(canavar[i].etki, "trol") != NULL)
                    {
                        birliklerim[7].kritik_sans += birliklerim[7].kritik_sans * canavar[i].bonus_degeri/100;
                    }
                }
            }
        }

        // ORK arastirma deger guncelle
        for(int i=0; i<4; i++)
        {
            if( senaryomuz.org_arastirmasi[3] == arastirma[i].adi[3] )
            {
                if( strstr(arastirma[i].adi,"elit") != NULL)
                {
                    if(senaryomuz.org_arastirma_seviyesi == 1)
                    {
                        birliklerim[4].kritik_sans +=  birliklerim[4].kritik_sans * arastirma[i].seviye1/100;
                        birliklerim[5].kritik_sans +=  birliklerim[5].kritik_sans * arastirma[i].seviye1/100;
                        birliklerim[6].kritik_sans +=  birliklerim[6].kritik_sans * arastirma[i].seviye1/100;
                        birliklerim[7].kritik_sans +=  birliklerim[7].kritik_sans * arastirma[i].seviye1/100;
                    }
                    if(senaryomuz.org_arastirma_seviyesi == 2)
                    {
                        birliklerim[4].kritik_sans +=  birliklerim[4].kritik_sans * arastirma[i].seviye2/100;
                        birliklerim[5].kritik_sans +=  birliklerim[5].kritik_sans * arastirma[i].seviye2/100;
                        birliklerim[6].kritik_sans +=  birliklerim[6].kritik_sans * arastirma[i].seviye2/100;
                        birliklerim[7].kritik_sans +=  birliklerim[7].kritik_sans * arastirma[i].seviye2/100;
                    }
                    if(senaryomuz.org_arastirma_seviyesi == 3)
                    {
                        birliklerim[4].kritik_sans +=  birliklerim[4].kritik_sans * arastirma[i].seviye3/100;
                        birliklerim[5].kritik_sans +=  birliklerim[5].kritik_sans * arastirma[i].seviye3/100;
                        birliklerim[6].kritik_sans +=  birliklerim[6].kritik_sans * arastirma[i].seviye3/100;
                        birliklerim[7].kritik_sans +=  birliklerim[7].kritik_sans * arastirma[i].seviye3/100;
                    }
                }
                if( strstr(arastirma[i].adi,"saldiri_gelistirmesi") != NULL)
                {
                    if(senaryomuz.org_arastirma_seviyesi == 1)
                    {
                        birliklerim[4].saldiri += birliklerim[4].saldiri * arastirma[i].seviye1/100;
                        birliklerim[5].saldiri += birliklerim[5].saldiri * arastirma[i].seviye1/100;
                        birliklerim[6].saldiri += birliklerim[6].saldiri * arastirma[i].seviye1/100;
                        birliklerim[7].saldiri += birliklerim[7].saldiri * arastirma[i].seviye1/100;
                    }
                    if(senaryomuz.org_arastirma_seviyesi == 2)
                    {
                        birliklerim[4].saldiri += birliklerim[4].saldiri * arastirma[i].seviye2/100;
                        birliklerim[5].saldiri += birliklerim[5].saldiri * arastirma[i].seviye2/100;
                        birliklerim[6].saldiri += birliklerim[6].saldiri * arastirma[i].seviye2/100;
                        birliklerim[7].saldiri += birliklerim[7].saldiri * arastirma[i].seviye2/100;
                    }
                    if(senaryomuz.org_arastirma_seviyesi == 3)
                    {
                        birliklerim[4].saldiri += birliklerim[4].saldiri * arastirma[i].seviye3/100;
                        birliklerim[5].saldiri += birliklerim[5].saldiri * arastirma[i].seviye3/100;
                        birliklerim[6].saldiri += birliklerim[6].saldiri * arastirma[i].seviye3/100;
                        birliklerim[7].saldiri += birliklerim[7].saldiri * arastirma[i].seviye3/100;
                    }
                }
                if (strstr(arastirma[i].adi, "savunma_ustaligi") != NULL)
                {
                    if (senaryomuz.org_arastirma_seviyesi == 1)
                    {
                        birliklerim[4].savunma += birliklerim[4].savunma * arastirma[i].seviye1 / 100;
                        birliklerim[5].savunma += birliklerim[5].savunma * arastirma[i].seviye1 / 100;
                        birliklerim[6].savunma += birliklerim[6].savunma * arastirma[i].seviye1 / 100;
                        birliklerim[7].savunma += birliklerim[7].savunma * arastirma[i].seviye1 / 100;
                    }
                    if (senaryomuz.org_arastirma_seviyesi == 2)
                    {
                        birliklerim[4].savunma += birliklerim[4].savunma * arastirma[i].seviye2 / 100;
                        birliklerim[5].savunma += birliklerim[5].savunma * arastirma[i].seviye2 / 100;
                        birliklerim[6].savunma += birliklerim[6].savunma * arastirma[i].seviye2 / 100;
                        birliklerim[7].savunma += birliklerim[7].savunma * arastirma[i].seviye2 / 100;
                    }
                    if (senaryomuz.org_arastirma_seviyesi == 3)
                    {
                        birliklerim[4].savunma += birliklerim[4].savunma * arastirma[i].seviye3 / 100;
                        birliklerim[5].savunma += birliklerim[5].savunma * arastirma[i].seviye3 / 100;
                        birliklerim[6].savunma += birliklerim[6].savunma * arastirma[i].seviye3 / 100;
                        birliklerim[7].savunma += birliklerim[7].savunma * arastirma[i].seviye3 / 100;
                    }
                }
            }
        }

        //ORK kahraman deger guncelle
        for(int i=0; i<9; i++)
        {
            if (strstr(senaryomuz.org_kahramanlar, kahraman[i].ad) != NULL)
            {
                if (strstr(kahraman[i].bonus_turu, "saldiri") != NULL)
                {
                    if (strstr(kahraman[i].etki, "ork_dovuscu") != NULL)
                    {
                        birliklerim[4].saldiri += birliklerim[4].saldiri * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "mizrakci") != NULL)
                    {
                        birliklerim[5].saldiri += birliklerim[5].saldiri * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "varg") != NULL)
                    {
                        birliklerim[6].saldiri += birliklerim[6].saldiri * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "trol") != NULL)
                    {
                        birliklerim[7].saldiri += birliklerim[7].saldiri * kahraman[i].bonus_degeri / 100;
                    }
                }
                if (strstr(kahraman[i].bonus_turu, "savunma") != NULL)
                {
                    if (strstr(kahraman[i].etki, "ork_dovuscu") != NULL)
                    {
                        birliklerim[4].savunma += birliklerim[4].savunma * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "mizrakci") != NULL)
                    {
                        birliklerim[5].savunma += birliklerim[5].savunma * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "varg") != NULL)
                    {
                        birliklerim[6].savunma += birliklerim[6].savunma * kahraman[i].bonus_degeri / 100;
                    }
                    if (strstr(kahraman[i].etki, "trol") != NULL)
                    {
                        birliklerim[7].savunma += birliklerim[7].savunma * kahraman[i].bonus_degeri / 100;
                    }
                }
                if (strstr(kahraman[i].bonus_turu, "kritik_sans") != NULL)
                {
                    if (strstr(kahraman[i].etki, "ork_dovuscu") != NULL)
                    {
                        birliklerim[4].kritik_sans += birliklerim[4].kritik_sans * kahraman[i].bonus_degeri/100;
                    }
                    if (strstr(kahraman[i].etki, "mizrakci") != NULL)
                    {
                        birliklerim[5].kritik_sans += birliklerim[5].kritik_sans * kahraman[i].bonus_degeri/100;
                    }
                    if (strstr(kahraman[i].etki, "varg") != NULL)
                    {
                        birliklerim[6].kritik_sans += birliklerim[6].kritik_sans * kahraman[i].bonus_degeri/100;
                    }
                    if (strstr(kahraman[i].etki, "trol") != NULL)
                    {
                        birliklerim[7].kritik_sans += birliklerim[7].kritik_sans * kahraman[i].bonus_degeri/100;
                    }
                }
            }
        }
    }

    double insan_saldiri_gucu = birliklerim[0].saldiri * senaryomuz.piyadeler + birliklerim[1].saldiri * senaryomuz.okcular + birliklerim[2].saldiri * senaryomuz.suvariler + birliklerim[3].saldiri * senaryomuz.kusatma_makineleri ;
    double insan_savunma_gucu = birliklerim[0].savunma * senaryomuz.piyadeler + birliklerim[1].savunma * senaryomuz.okcular + birliklerim[2].savunma * senaryomuz.suvariler + birliklerim[3].savunma * senaryomuz.kusatma_makineleri ;
    double insan_saglik = birliklerim[0].saglik * senaryomuz.piyadeler + birliklerim[1].saglik * senaryomuz.okcular + birliklerim[2].saglik * senaryomuz.suvariler + birliklerim[3].saglik * senaryomuz.kusatma_makineleri ;

    double ork_saldiri_gucu = birliklerim[4].saldiri * senaryomuz.piyadeler + birliklerim[5].saldiri * senaryomuz.okcular + birliklerim[6].saldiri * senaryomuz.suvariler + birliklerim[7].saldiri * senaryomuz.kusatma_makineleri ;
    double ork_savunma_gucu = birliklerim[4].savunma * senaryomuz.piyadeler + birliklerim[5].savunma * senaryomuz.okcular + birliklerim[6].savunma * senaryomuz.suvariler + birliklerim[7].savunma * senaryomuz.kusatma_makineleri ;
    double ork_saglik = birliklerim[4].saglik * senaryomuz.piyadeler + birliklerim[5].saglik * senaryomuz.okcular + birliklerim[6].saglik * senaryomuz.suvariler + birliklerim[7].saglik * senaryomuz.kusatma_makineleri ;

    double insan_net_hasar;
    double ork_net_hasar;

    double piyade_saglik = senaryomuz.piyadeler * birliklerim[0].saglik;
    double okcu_saglik = senaryomuz.okcular * birliklerim[1].saglik;
    double suvari_saglik = senaryomuz.suvariler * birliklerim[2].saglik;
    double kusatma_saglik = senaryomuz.kusatma_makineleri * birliklerim[3].saglik;

    double ork_dovuscu_saglik = senaryomuz.org_dovusculeri * birliklerim[4].saglik;
    double mizrakci_saglik = senaryomuz.mizrakcilar * birliklerim[5].saglik;
    double varg_binici_saglik = senaryomuz.varg_binicileri * birliklerim[6].saglik;
    double troller_saglik = senaryomuz.troller * birliklerim[7].saglik;


    double ilk_piyade_saglik = piyade_saglik;
    double ilk_okcu_saglik = okcu_saglik;
    double ilk_suvari_saglik = suvari_saglik;
    double ilk_kusatma_saglik = kusatma_saglik;

    double ilk_ork_dovuscu_saglik = ork_dovuscu_saglik;
    double ilk_mizrakci_saglik = mizrakci_saglik;
    double ilk_varg_binici_saglik = varg_binici_saglik;
    double ilk_troller_saglik = troller_saglik;

    FILE *yazdir = fopen("sonuclar.txt","w");

    if(yazdir == NULL)
    {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    int adim = 0;
    int adim2 = 0;

    void durum_yazdir()
    {
        fprintf(yazdir,"%d. adim\n",adim);
        fprintf(yazdir,"-------------------------------------\n");
        fprintf(yazdir,"INSAN IMPARATORLUGU\n");
        fprintf(yazdir,"Piyade saglik         : %.2lf\n",piyade_saglik);
        fprintf(yazdir,"Okcu saglik           : %.2lf\n",okcu_saglik);
        fprintf(yazdir,"Suvari saglik         : %.2lf\n",suvari_saglik);
        fprintf(yazdir,"Kusatma saglik        : %.2lf\n",kusatma_saglik);
        fprintf(yazdir,"---------------------\n");
        fprintf(yazdir,"ORK LEGI\n");
        fprintf(yazdir,"Ork dovuscu saglik    : %.2lf\n",ork_dovuscu_saglik);
        fprintf(yazdir,"Mizrakci saglik       : %.2lf\n",mizrakci_saglik);
        fprintf(yazdir,"Varg binicisi saglik  : %.2lf\n",varg_binici_saglik);
        fprintf(yazdir,"Troller saglik        : %.2lf\n",troller_saglik);
        fprintf(yazdir,"---------------------\n");
        fprintf(yazdir,"Insanlara Net Hasar   : %.2lf\n",insan_net_hasar);
        fprintf(yazdir,"Orklara Net Hasar     : %.2lf\n",ork_net_hasar);
        fprintf(yazdir,"V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V\n\n");

    }
    while( insan_saglik > 0 && ork_saglik > 0)
    {
        guncelleme_yap();

        for (int a=0; a<8; a++)
        {
            if ( birliklerim[a].kritik_sans  == adim )
            {
                birliklerim[a].saldiri += birliklerim[a].saldiri/2;
            }
        }
        for (int a=0; a<8; a++)
        {
            if (adim2==5)
            {
                birliklerim[a].saldiri -= birliklerim[a].saldiri/10;
                birliklerim[a].savunma -= birliklerim[a].saldiri/10;
                adim2=0;
            }
        }

        insan_saldiri_gucu = birliklerim[0].saldiri * senaryomuz.piyadeler + birliklerim[1].saldiri * senaryomuz.okcular + birliklerim[2].saldiri * senaryomuz.suvariler + birliklerim[3].saldiri * senaryomuz.kusatma_makineleri ;
        insan_savunma_gucu = birliklerim[0].savunma * senaryomuz.piyadeler + birliklerim[1].savunma * senaryomuz.okcular + birliklerim[2].savunma * senaryomuz.suvariler + birliklerim[3].savunma * senaryomuz.kusatma_makineleri ;
        ork_saldiri_gucu = birliklerim[4].saldiri * senaryomuz.piyadeler + birliklerim[5].saldiri * senaryomuz.okcular + birliklerim[6].saldiri * senaryomuz.suvariler + birliklerim[7].saldiri * senaryomuz.kusatma_makineleri ;
        ork_savunma_gucu = birliklerim[4].savunma * senaryomuz.piyadeler + birliklerim[5].savunma * senaryomuz.okcular + birliklerim[6].savunma * senaryomuz.suvariler + birliklerim[7].savunma * senaryomuz.kusatma_makineleri ;
        adim++;
        adim2++;

        if (insan_saldiri_gucu >= ork_savunma_gucu)
        {
            ork_saglik -= insan_saldiri_gucu - ork_savunma_gucu;
            ork_net_hasar = insan_saldiri_gucu - ork_savunma_gucu;
            if(senaryomuz.org_dovusculeri > 0 && ork_dovuscu_saglik > 0)
            {
                ork_dovuscu_saglik -= ork_net_hasar *((senaryomuz.org_dovusculeri * birliklerim[4].savunma)/ork_savunma_gucu);
                if(ork_dovuscu_saglik <= 0)
                {
                    ork_dovuscu_saglik=0;
                }

            }
            if(senaryomuz.mizrakcilar > 0 && mizrakci_saglik > 0)
            {
                mizrakci_saglik -= ork_net_hasar *((senaryomuz.mizrakcilar * birliklerim[5].savunma)/ork_savunma_gucu);
                if(mizrakci_saglik <= 0)
                {
                    mizrakci_saglik=0;
                }

            }
            if(senaryomuz.varg_binicileri > 0 && varg_binici_saglik > 0)
            {
                varg_binici_saglik -= ork_net_hasar *((senaryomuz.varg_binicileri * birliklerim[6].savunma)/ork_savunma_gucu);
                if(varg_binici_saglik <= 0)
                {
                    varg_binici_saglik=0;
                }

            }
            if(senaryomuz.troller > 0 && troller_saglik > 0)
            {
                troller_saglik -= ork_net_hasar *((senaryomuz.troller * birliklerim[7].savunma)/ork_savunma_gucu);
                if(troller_saglik <= 0)
                {
                    troller_saglik=0;
                }
            }

        }
        if (ork_saglik <= 0)
        {
            ork_saglik = 0;
            ork_dovuscu_saglik=0;
            mizrakci_saglik=0;
            varg_binici_saglik=0;
            troller_saglik=0;
            durum_yazdir();
            fprintf(yazdir,"INSANLAR KAZANDI!\n");
            break;
        }
        if (ork_saldiri_gucu >= insan_savunma_gucu)
        {
            insan_saglik -= ork_saldiri_gucu - insan_savunma_gucu;
            insan_net_hasar = ork_saldiri_gucu - insan_savunma_gucu;
            if(senaryomuz.piyadeler > 0 && piyade_saglik > 0)
            {
                piyade_saglik -= insan_net_hasar *((senaryomuz.piyadeler * birliklerim[0].savunma)/insan_savunma_gucu);
                if(piyade_saglik <= 0)
                {
                    piyade_saglik=0;
                }
            }
            if(senaryomuz.okcular > 0 && okcu_saglik >0)
            {
                okcu_saglik -= insan_net_hasar *((senaryomuz.okcular * birliklerim[1].savunma)/insan_savunma_gucu);
                if(okcu_saglik <=0)
                {
                    okcu_saglik=0;
                }
            }
            if(senaryomuz.suvariler > 0 && suvari_saglik >0)
            {
                suvari_saglik -= insan_net_hasar *((senaryomuz.suvariler * birliklerim[2].savunma)/insan_savunma_gucu);
                if(suvari_saglik <= 0)
                {
                    suvari_saglik=0;

                }
            }
            if(senaryomuz.kusatma_makineleri > 0 && kusatma_saglik >0)
            {
                kusatma_saglik -= insan_net_hasar *((senaryomuz.kusatma_makineleri * birliklerim[3].savunma)/insan_savunma_gucu);
                if(kusatma_saglik <= 0)
                {
                    kusatma_saglik=0;
                }

            }
        }
        if (insan_saglik <= 0)
        {
            insan_saglik = 0;
            piyade_saglik=0;
            okcu_saglik=0;
            suvari_saglik=0;
            kusatma_saglik=0;
            durum_yazdir();
            fprintf(yazdir,"ORKLAR KAZANDI!\n");
            break;
        }

        // Dosyaya Yazmak icin

        durum_yazdir();

    }
    fclose(yazdir);

    double piyade_bar = 100*(piyade_saglik/ilk_piyade_saglik);
    double okcu_bar = 100*(okcu_saglik/ilk_okcu_saglik);
    double suvari_bar = 100*(suvari_saglik/ilk_suvari_saglik);
    double kusatma_bar = 100*(kusatma_saglik/ilk_kusatma_saglik);

    double ork_dovuscu_bar = 100*(ork_dovuscu_saglik/ilk_ork_dovuscu_saglik);
    double mizrakci_bar = 100*(mizrakci_saglik/ilk_mizrakci_saglik);
    double varg_binici_bar = 100*(varg_binici_saglik/ilk_varg_binici_saglik);
    double troller_bar = 100*(troller_saglik/ilk_troller_saglik);

    // oyun müziğini yüklemek için gerekli değişkenler
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;

    // müziği yükleme kısmı
    if (SDL_LoadWAV("oyunmuzigi.wav", &wavSpec, &wavBuffer, &wavLength) == NULL)
    {
        printf("WAV dosyası yüklenemedi! SDL Hatası: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // müziği başlatma kontrolü
    if (SDL_OpenAudio(&wavSpec, NULL) < 0)
    {
        printf("Ses oynatılamadı! SDL Hatası: %s\n", SDL_GetError());
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();
        return -1;
    }

    // müziği başlat
    SDL_PauseAudio(0);
    SDL_QueueAudio(1, wavBuffer, wavLength);

    // sdl,sdl_ttf gibi kütüphanelerin kontrolü
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL başlatılamadı! SDL Hatası: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf başlatilamadi! TTF Hatası: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        printf("SDL_image başlatılamadı! SDL_image Hatası: %s\n", IMG_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Savaş Simülasyonu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Pencere oluşturulamadı! SDL Hatası: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer oluşturulamadı! SDL Hatası: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // ikinci ekran için gerekli değişkenler
    SDL_Window* secondWindow = NULL;
    SDL_Renderer* secondRenderer = NULL;
    int secondWindowOpened = 0; // ikinci pencere kontrolü

    // arkaplan fotoğrafını yükleme kısmı
    SDL_Texture* backgroundTexture = loadPNGTexture("background1.png", renderer);
    if (backgroundTexture == NULL)
    {
        printf("Arka plan PNG dosyası yüklenemedi!\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // birlik,kahraman ve canavar dosyalarını yükleme
    SDL_Texture* characters[28];
    characters[0] = loadPNGTexture("piyade.png", renderer);
    characters[1] = loadPNGTexture("okcu.png", renderer);
    characters[2] = loadPNGTexture("suvari.png", renderer);
    characters[3] = loadPNGTexture("kusatma_makinesi.png", renderer);
    characters[4] = loadPNGTexture("ork_dovuscu.png", renderer);
    characters[5] = loadPNGTexture("mizrakci.png", renderer);
    characters[6] = loadPNGTexture("varg_binicisi.png", renderer);
    characters[7] = loadPNGTexture("troller.png", renderer);
    characters[8] = loadPNGTexture("alparslan.png", renderer);
    characters[9] = loadPNGTexture("fsm.png", renderer);
    characters[10] = loadPNGTexture("metehan.png", renderer);
    characters[11] = loadPNGTexture("yss.png", renderer);
    characters[12] = loadPNGTexture("tugrulbey.png", renderer);
    characters[13] = loadPNGTexture("gorukvahsi.png", renderer);
    characters[14] = loadPNGTexture("thruk.png", renderer);
    characters[15] = loadPNGTexture("vrog.png", renderer);
    characters[16] = loadPNGTexture("ugarzalim.png", renderer);
    characters[17] = loadPNGTexture("ejderha.png", renderer);
    characters[18] = loadPNGTexture("agridagidevleri.png", renderer);
    characters[19] = loadPNGTexture("tepegoz.png", renderer);
    characters[20] = loadPNGTexture("karakurt.png", renderer);
    characters[21] = loadPNGTexture("samur.png", renderer);
    characters[22] = loadPNGTexture("karatroll.png", renderer);
    characters[23] = loadPNGTexture("golgekurtlari.png", renderer);
    characters[24] = loadPNGTexture("camurdevleri.png", renderer);
    characters[25] = loadPNGTexture("atesiblisi.png", renderer);
    characters[26] = loadPNGTexture("makrog.png", renderer);
    characters[27] = loadPNGTexture("buzdevleri.png", renderer);

    for (int i = 0; i < 28; ++i)
    {
        if (characters[i] == NULL)
        {
            printf("Karakter %d PNG dosyası yüklenemedi!\n", i + 1);
            for (int j = 0; j <= i; ++j)
            {
                SDL_DestroyTexture(characters[j]);
            }
            SDL_DestroyTexture(backgroundTexture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    TTF_Font* font = TTF_OpenFont("Arial2.ttf", 20);
    if (font == NULL)
    {
        printf("Font yüklenemedi! TTF Hatası: %s\n", TTF_GetError());
        for (int i = 0; i < 28; ++i)
        {
            SDL_DestroyTexture(characters[i]);
        }
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Color white = {0, 0, 0, 255};

    srand(time(NULL));

    // ızgaradakileri kareleri yapı içinde oluşturma kısmı

    struct Tile grid[GRID_ROWS][GRID_COLS] = {0}; // kareleri sıfıra eşitledik

    //burada karelere rastgele png yükleme var
    for (int i = 0; i < GRID_ROWS; ++i)
    {
        for (int j = 0; j < GRID_COLS; ++j)
        {
            // kahraman ve birlik arasında boşluk bırakma
            if (j == 0 || j == GRID_COLS - 1 || j == (GRID_COLS / 2) || j == (GRID_COLS / 2) - 1)
            {
                grid[i][j].characterIndex = -1;  // karakter indeksi -1 olursa karakter koymaz
            }
            else
            {
                grid[i][j].unitCount = rand() % (MAX_UNITS_PER_TILE + 1);
                grid[i][j].health = rand() % 101;

                if (j < (GRID_COLS / 2) - 1)
                {

                    grid[i][j].characterIndex=-1; // karakter indeksi -1 olursa karakter koymaz
                }

                else if (j > (GRID_COLS / 2))
                {
                    grid[i][j].characterIndex=-1; // karakter indeksi -1 olursa karakter koymaz
                }
            }
        }
    }

//piyade
    if(senaryomuz.piyadeler>0)
    {
        int piyadesayisi=senaryomuz.piyadeler;
        grid[0][5].characterIndex=0;
        grid[0][5].unitCount=piyadesayisi;
        int tasma =grid[0][5].unitCount-100;
        if(tasma>0)
        {
            int dongu=(grid[0][5].unitCount/100);
            if(grid[0][5].unitCount%100!=0)
            {
                dongu++;
                for(int a=1; a<dongu; a++)
                {
                    if(grid[a][5].characterIndex==-1)
                    {
                        grid[a][5].characterIndex=0;
                        grid[a][5].unitCount=tasma;
                        grid[a][5].health=100;
                        grid[a][5].unitCount=grid[0][5].unitCount-tasma;
                    }
                }
            }
            else
            {
                for(int a=1; a<dongu; a++)
                {
                    if(grid[a][5].characterIndex==-1)
                    {
                        grid[a][5].characterIndex=0;
                        grid[a][5].unitCount=tasma;
                        grid[a][5].health=100;
                        grid[a][5].unitCount=grid[0][5].unitCount-tasma;
                    }
                }
            }
            if(piyadesayisi%100==0)
                grid[0][5].unitCount=100;

            else
                grid[0][5].unitCount=piyadesayisi%100;

        }
        grid[0][5].health=100;
    }

//okcu
    if(senaryomuz.okcular>0)
    {
        int okcusayisi=senaryomuz.okcular;
        grid[0][3].characterIndex=1;
        grid[0][3].unitCount=okcusayisi;
        int tasma2 =grid[0][3].unitCount-100;
        if(tasma2>0)
        {
            int dongu2=(grid[0][3].unitCount/100);
            if(grid[0][3].unitCount%100!=0)
            {
                dongu2++;

                for(int a=1; a<dongu2; a++)
                {
                    if(grid[a][3].characterIndex==-1)
                    {
                        grid[a][3].characterIndex=1;
                        grid[a][3].unitCount=tasma2;
                        grid[a][3].health=100;
                        grid[a][3].unitCount=grid[0][3].unitCount-tasma2;
                    }
                }
            }
            else
            {
                for(int a=1; a<dongu2; a++)
                {
                    if(grid[a][3].characterIndex==-1)
                    {
                        grid[a][3].characterIndex=1;
                        grid[a][3].unitCount=tasma2;
                        grid[a][3].health=100;
                        grid[a][3].unitCount=grid[0][3].unitCount-tasma2;
                    }
                }
            }
            if(okcusayisi%100==0)
                grid[0][3].unitCount=100;
            else
                grid[0][3].unitCount=okcusayisi%100;
        }
        grid[0][3].health=100;
    }

//suvari
    if(senaryomuz.suvariler>0)
    {
        int suvarisayisi=senaryomuz.suvariler;
        grid[0][4].characterIndex=2;
        grid[0][4].unitCount=suvarisayisi;
        int tasma3 =grid[0][4].unitCount-100;
        if(tasma3>0)
        {
            int dongu3=(grid[0][4].unitCount/100);
            if(grid[0][4].unitCount%100!=0)
            {
                dongu3++;

                for(int a=1; a<dongu3; a++)
                {
                    if(grid[a][4].characterIndex==-1)
                    {
                        grid[a][4].characterIndex=2;
                        grid[a][4].unitCount=tasma3;
                        grid[a][4].health=100;
                        grid[a][4].unitCount=grid[0][4].unitCount-tasma3;
                    }

                }
            }
            else
            {
                for(int a=1; a<dongu3; a++)
                {
                    if(grid[a][4].characterIndex==-1)
                    {
                        grid[a][4].characterIndex=2;
                        grid[a][4].unitCount=tasma3;
                        grid[a][4].health=100;
                        grid[a][4].unitCount=grid[0][4].unitCount-tasma3;
                    }

                }
            }
            if(suvarisayisi%100==0)
                grid[0][4].unitCount=100;

            else
                grid[0][4].unitCount=suvarisayisi%100;

        }
        grid[0][4].health=100;

    }

//kusatma
    if(senaryomuz.kusatma_makineleri>0)
    {
        int kusatmasayisi=senaryomuz.kusatma_makineleri;
        grid[0][2].characterIndex=3;
        grid[0][2].unitCount=kusatmasayisi;
        int tasma4 =grid[0][2].unitCount-100;
        if(tasma4>0)
        {
            int dongu4=(grid[0][2].unitCount/100);

            if(grid[0][2].unitCount%100!=0)
            {
                dongu4++;

                for(int a=1; a<dongu4; a++)
                {
                    if(grid[a][2].characterIndex==-1)
                    {
                        grid[a][2].characterIndex=3;
                        grid[a][2].unitCount=tasma4;
                        grid[a][2].health=100;
                        grid[a][2].unitCount=grid[0][2].unitCount-tasma4;
                    }

                }
            }
            else
            {
                for(int a=1; a<dongu4; a++)
                {
                    if(grid[a][2].characterIndex==-1)
                    {
                        grid[a][2].characterIndex=3;
                        grid[a][2].unitCount=tasma4;
                        grid[a][2].health=100;
                        grid[a][2].unitCount=grid[0][2].unitCount-tasma4;
                    }

                }
            }
            if(kusatmasayisi%100==0)

                grid[0][2].unitCount=100;

            else
                grid[0][2].unitCount=kusatmasayisi%100;

        }
        grid[0][2].health=100;

    }

//ork dovuscusu

    if(senaryomuz.org_dovusculeri > 0)
    {
        int orgDovusculeriSayisi = senaryomuz.org_dovusculeri;
        grid[0][9].characterIndex = 4;
        grid[0][9].unitCount = orgDovusculeriSayisi;
        int tasma5 = grid[0][9].unitCount - 100;

        if (tasma5 > 0)
        {
            int dongu5=(grid[0][9].unitCount / 100);

            if(grid[0][9].unitCount%100!=0)
            {
                dongu5++;
                for (int a = 1; a <dongu5; a++)
                {
                    if (grid[a][9].characterIndex == -1)
                    {
                        grid[a][9].characterIndex = 4;
                        grid[a][9].unitCount = tasma5;
                        grid[a][9].health = 100;
                        grid[a][9].unitCount = grid[0][9].unitCount - tasma5;
                    }
                }
            }
            else
            {
                for (int a = 1; a <dongu5; a++)
                {
                    if (grid[a][9].characterIndex == -1)
                    {
                        grid[a][9].characterIndex = 4;
                        grid[a][9].unitCount = tasma5;
                        grid[a][9].health = 100;
                        grid[a][9].unitCount = grid[0][9].unitCount - tasma5;
                    }
                }
            }

            if (orgDovusculeriSayisi % 100 == 0)
                grid[0][9].unitCount = 100;
            else
                grid[0][9].unitCount = orgDovusculeriSayisi % 100;
        }

        grid[0][9].health = 100;
    }

//mizrakcilar
    if(senaryomuz.mizrakcilar > 0)
    {
        int mizrakcisayisi = senaryomuz.mizrakcilar;
        grid[0][11].characterIndex = 5;
        grid[0][11].unitCount = mizrakcisayisi;
        int tasma6 = grid[0][11].unitCount - 100;

        if(tasma6 > 0)
        {
            int dongu6=(grid[0][11].unitCount / 100);
            if(grid[0][11].unitCount%100!=0)
            {
                dongu6++;
                for(int a = 1; a <dongu6; a++)
                {
                    if(grid[a][11].characterIndex == -1)
                    {
                        grid[a][11].characterIndex = 5;
                        grid[a][11].unitCount = tasma6;
                        grid[a][11].health = 100;
                        grid[a][11].unitCount = grid[0][11].unitCount - tasma6;
                    }
                }
            }
            else
            {
                for(int a = 1; a <dongu6; a++)
                {
                    if(grid[a][11].characterIndex == -1)
                    {
                        grid[a][11].characterIndex = 5;
                        grid[a][11].unitCount = tasma6;
                        grid[a][11].health = 100;
                        grid[a][11].unitCount = grid[0][11].unitCount - tasma6;
                    }
                }
            }

            if(mizrakcisayisi % 100 == 0)
                grid[0][11].unitCount = 100;
            else
                grid[0][11].unitCount = mizrakcisayisi % 100;
        }

        grid[0][11].health = 100;
    }

//varg binicisi
    if(senaryomuz.varg_binicileri > 0)
    {
        int vargsayisi = senaryomuz.varg_binicileri;
        grid[0][10].characterIndex = 6;
        grid[0][10].unitCount = vargsayisi;
        int tasma7 = grid[0][10].unitCount - 100;

        if(tasma7 > 0)
        {
            int dongu7=(grid[0][10].unitCount / 100);
            if(grid[0][10].unitCount%100!=0)
            {
                dongu7++;

                for(int a = 1; a <dongu7; a++)
                {
                    if(grid[a][10].characterIndex == -1)
                    {
                        grid[a][10].characterIndex = 6;
                        grid[a][10].unitCount = tasma7;
                        grid[a][10].health = 100;
                        grid[a][10].unitCount = grid[0][10].unitCount - tasma7;
                    }
                }
            }
            else
            {
                for(int a = 1; a <dongu7; a++)
                {
                    if(grid[a][10].characterIndex == -1)
                    {
                        grid[a][10].characterIndex = 6;
                        grid[a][10].unitCount = tasma7;
                        grid[a][10].health = 100;
                        grid[a][10].unitCount = grid[0][10].unitCount - tasma7;
                    }
                }
            }

            if(vargsayisi % 100 == 0)
                grid[0][10].unitCount = 100;
            else
                grid[0][10].unitCount = vargsayisi % 100;
        }

        grid[0][10].health = 100;
    }

//troller

    if(senaryomuz.troller > 0)
    {
        int trolsayisi = senaryomuz.troller;
        grid[0][12].characterIndex = 7;
        grid[0][12].unitCount = trolsayisi;
        int tasma8 = grid[0][12].unitCount - 100;

        if(tasma8 > 0)
        {
            int dongu8=(grid[0][12].unitCount / 100);

            if(grid[0][12].unitCount%100!=0)
            {
                dongu8++;
                for(int a = 1; a < dongu8; a++)
                {
                    if(grid[a][12].characterIndex == -1)
                    {
                        grid[a][12].characterIndex = 7;
                        grid[a][12].unitCount = tasma8;
                        grid[a][12].health = 100;
                        grid[a][12].unitCount = grid[0][12].unitCount - tasma8;
                    }
                }
            }
            else
            {
                for(int a = 1; a < dongu8; a++)
                {
                    if(grid[a][12].characterIndex == -1)
                    {
                        grid[a][12].characterIndex = 7;
                        grid[a][12].unitCount = tasma8;
                        grid[a][12].health = 100;
                        grid[a][12].unitCount = grid[0][12].unitCount - tasma8;
                    }
                }
            }
            if(trolsayisi % 100 == 0)
                grid[0][12].unitCount = 100;
            else
                grid[0][12].unitCount = trolsayisi % 100;
        }

        grid[0][12].health = 100;
    }

    void insan_kahraman_ara(char isim[20],int a)
    {
        if(strstr(senaryomuz.insan_kahramanlar,isim))
        {
            grid[0][0].characterIndex=a;
            grid[0][0].unitCount=1;
            grid[0][0].health=100;

        }
    }

    insan_kahraman_ara("Alparslan",8);
    insan_kahraman_ara("Fatih",9);
    insan_kahraman_ara("Mete",10);
    insan_kahraman_ara("Yavuz_Sultan",11);
    insan_kahraman_ara("Tugrul",12);

    void insan_canavar_ara(char isim[20],int a)
    {
        if(strstr(senaryomuz.insan_canavarlar,isim))
        {
            grid[9][0].characterIndex=a;
            grid[9][0].unitCount=1;
            grid[9][0].health=100;
        }
    }

    insan_canavar_ara("Ejderha",17);
    insan_canavar_ara("Agri",18);
    insan_canavar_ara("Tepegoz",19);
    insan_canavar_ara("Karakurt",20);
    insan_canavar_ara("Samur",21);

    void ork_kahraman_ara(char isim[20],int a)
    {
        if(strstr(senaryomuz.org_kahramanlar,isim))
        {
            grid[0][14].characterIndex=a;
            grid[0][14].unitCount=1;
            grid[0][14].health=100;
        }
    }

    ork_kahraman_ara("Goruk",13);
    ork_kahraman_ara("Thruk",14);
    ork_kahraman_ara("Vrog",15);
    ork_kahraman_ara("Ugar",16);

    void ork_canavar_ara(char isim[20],int a)
    {
        if(strstr(senaryomuz.org_canavarlar,isim))
        {
            grid[9][14].characterIndex=a;
            grid[9][14].unitCount=1;
            grid[9][14].health=100;
        }
    }

    ork_canavar_ara("Kara_Troll",22);
    ork_canavar_ara("Golge",23);
    ork_canavar_ara("Camur",24);
    ork_canavar_ara("Ates",25);
    ork_canavar_ara("Makrog",26);
    ork_canavar_ara("Buz",27);

    int quit = 0;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN && !secondWindowOpened)
            {
                // eğer enter tuşuna basılırsa ikinci adıma geç

                SDL_Texture* countdownBackground = loadPNGTexture("background.png", renderer);
                // geçiş yaparken 4 sn beklet
                for (int countdown = 4; countdown > 0; --countdown)
                {
                    SDL_RenderClear(renderer);

                    if (countdownBackground != NULL)
                    {
                        SDL_RenderCopy(renderer, countdownBackground, NULL, NULL);  // bekleme arkaplanını getir
                    }

                    // ekrana simüle ediliyor diye mesaj taz
                    TTF_Font* font = TTF_OpenFont("Arial2.ttf", 70);
                    displayText(renderer, font, "Simule ediliyor...");
                    SDL_RenderPresent(renderer);

                    SDL_Delay(1000);  // döngü aralarında 1sn bekle
                }
                secondWindow = SDL_CreateWindow("Savaş Simülasyonu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
                secondRenderer = SDL_CreateRenderer(secondWindow, -1, SDL_RENDERER_ACCELERATED);
                secondWindowOpened = 1;
                SDL_DestroyTexture(countdownBackground);
                if(insan_saglik==0)
                {
                    for(int i=0; i<10; i++)
                    {
                        for(int j=0; j<6; j++)
                            grid[i][j].characterIndex=-1; //insan sağlığı bittiyse insan tarafındaki tüm karakterleri yok et
                    }

                    for(int i=0; i<10; i++)
                    {

                        if(senaryomuz.org_dovusculeri>0)
                            grid[i][9].health=ork_dovuscu_bar;

                        if(senaryomuz.mizrakcilar>0)
                            grid[i][11].health=mizrakci_bar;

                        if(senaryomuz.varg_binicileri>0)
                            grid[i][10].health=varg_binici_bar;

                        if(senaryomuz.troller>0)
                            grid[i][12].health=troller_bar;

                    }

                }
                if(ork_saglik==0)
                {
                    for(int i=0; i<10; i++)
                    {
                        for(int j=9; j<15; j++)
                            grid[i][j].characterIndex=-1; //ork sağlığı sıfır ise ork kısmındaki her şeyi yok et
                    }

                    for(int i=0; i<10; i++)
                    {
                        if(senaryomuz.piyadeler>0)
                            grid[i][5].health=piyade_bar;

                        if(senaryomuz.okcular>0)
                            grid[i][3].health=okcu_bar;

                        if(senaryomuz.suvariler>0)
                            grid[i][4].health=suvari_bar;

                        if(senaryomuz.kusatma_makineleri>0)
                            grid[i][2].health=kusatma_bar;
                    }
                }
                // ikinci ekran için tekrardan karakterleri ve arkaplanı yükle
                backgroundTexture = loadPNGTexture("background1.png", secondRenderer);
                for (int i = 0; i < 28; ++i)
                {
                    characters[i] = loadPNGTexture(i == 0 ? "piyade.png" :
                                                   i == 1 ? "okcu.png" :
                                                   i == 2 ? "suvari.png" :
                                                   i == 3 ? "kusatma_makinesi.png" :
                                                   i == 4 ? "ork_dovuscu.png" :
                                                   i == 5 ? "mizrakci.png" :
                                                   i == 6 ? "varg_binicisi.png" :
                                                   i == 7 ? "troller.png" :
                                                   i == 8 ? "alparslan.png" :
                                                   i == 9 ? "fsm.png" :
                                                   i == 10 ? "metehan.png" :
                                                   i == 11 ? "yss.png" :
                                                   i == 12 ? "tugrulbey.png" :
                                                   i == 13 ? "gorukvahsi.png" :
                                                   i == 14 ? "thruk.png" :
                                                   i == 15 ? "vrog.png" :
                                                   i==  16 ? "ugarzalim.png" :
                                                   i == 17 ? "ejderha.png" :
                                                   i == 18 ? "agridagidevleri.png" :
                                                   i == 19 ? "tepegoz.png" :
                                                   i == 20 ? "karakurt.png" :
                                                   i == 21 ? "samur.png" :
                                                   i == 22 ? "karatroll.png" :
                                                   i == 23 ? "golgekurtlari.png" :
                                                   i == 24 ? "camurdevleri.png" :
                                                   i == 25 ? "atesiblisi.png" :
                                                   i == 26 ? "makrog.png" : "buzdevleri.png", secondRenderer);

                    if (characters[i] == NULL)
                    {
                        printf("Karakter %d PNG dosyası yüklenemedi!\n", i + 1);
                        break;
                    }
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        drawGrid(renderer);

        for (int i = 0; i < GRID_ROWS; ++i)
        {
            for (int j = 0; j < GRID_COLS; ++j)
            {
                int tileX = j * GRID_SIZE;
                int tileY = i * GRID_SIZE;

                if (grid[i][j].characterIndex != -1)
                {
                    int characterIndex = grid[i][j].characterIndex;
                    SDL_Rect characterRect = {tileX, tileY, GRID_SIZE, GRID_SIZE};
                    SDL_RenderCopy(renderer, characters[characterIndex], NULL, &characterRect);

                    if (grid[i][j].unitCount > 0 && grid[i][j].characterIndex != -1)
                    {
                        int healthBarX = tileX + 10;
                        int healthBarY = tileY + GRID_SIZE - 15;
                        int healthBarWidth = GRID_SIZE - 20;
                        int healthBarHeight = 7;
                        drawHealthBar(renderer, healthBarX, healthBarY, healthBarWidth, healthBarHeight, grid[i][j].health, 100);
                        drawUnitCountOnTile(renderer, font, white, grid[i][j].unitCount, tileX, tileY);  // can değerini her karaktere tanımlanmış bardan al


                        // eğer birlik sayıysı ve birlik canı sıfırdan büyükse can barı çiz
                        if(grid[i][j].unitCount>0 && grid[i][j].health>0)
                            drawHealthBar(renderer, healthBarX, healthBarY, healthBarWidth, healthBarHeight, grid[i][j].health, 100); // en fazla 100 can

                        // eğer birlik sayıysı ve birlik canı sıfırdan büyükse birlik sayısını yazdır
                        if(grid[i][j].unitCount>0 && grid[i][j].health>0)
                            drawUnitCountOnTile(renderer, font, white, grid[i][j].unitCount, tileX, tileY);
                    }
                }
            }
        }

        SDL_RenderPresent(renderer);  // 2.ekrana geç

        if (secondWindowOpened)
        {
            SDL_RenderClear(secondRenderer);

            // ikinci ekranda yeniden aynı arkaplanı kullan
            if (backgroundTexture != NULL)
            {
                SDL_RenderCopy(secondRenderer, backgroundTexture, NULL, NULL);
            }
            else
            {
                printf("İkinci pencerede arka plan resmi yüklenemedi!\n");
            }

            drawGrid(secondRenderer);

            for (int i = 0; i < GRID_ROWS; ++i)
            {
                for (int j = 0; j < GRID_COLS; ++j)
                {
                    int tileX = j * GRID_SIZE;
                    int tileY = i * GRID_SIZE;

                    // eğer birlik sayıysı ve birlik canı sıfırdan büyükse ve indeks -1 değilse ikinci pencerede karakterleri ekle
                    if (grid[i][j].characterIndex != -1 && grid[i][j].unitCount > 0 &&grid[i][j].health>0)
                    {
                        int characterIndex = grid[i][j].characterIndex;
                        SDL_Rect characterRect = {tileX, tileY, GRID_SIZE, GRID_SIZE};

                        // can barının konumunu büyüklüğünü ayarla
                        SDL_RenderCopy(secondRenderer, characters[characterIndex], NULL, &characterRect);

                        int healthBarX = tileX + 10;
                        int healthBarY = tileY + GRID_SIZE - 15;
                        int healthBarWidth = GRID_SIZE - 20;
                        int healthBarHeight = 7;
                        drawHealthBar(secondRenderer, healthBarX, healthBarY, healthBarWidth, healthBarHeight, grid[i][j].health, 100);
                        drawUnitCountOnTile(secondRenderer, font, white, grid[i][j].unitCount, tileX, tileY);
                    }
                }
            }
            SDL_RenderPresent(secondRenderer);
        }
    }

    TTF_CloseFont(font);
    SDL_DestroyTexture(backgroundTexture);

    for (int i = 0; i < 28; ++i)
    {
        SDL_DestroyTexture(characters[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    if (secondWindowOpened)
    {
        SDL_DestroyRenderer(secondRenderer);
        SDL_DestroyWindow(secondWindow);
    }

    SDL_FreeWAV(wavBuffer);
    SDL_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}