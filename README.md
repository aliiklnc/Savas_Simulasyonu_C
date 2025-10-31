# Savas_Simulasyonu_C
C programlama dili kullanılarak geliştirilmiş, İnsan İmparatorluğu ve Ork Lejyonu ırklarının yer aldığı ızgara tabanlı stratejik savaş simülasyonu.

# ⚔️ İnsan İmparatorluğu ve Ork Lejyonu Stratejik Savaş Simülasyonu

[cite_start]Bu proje, Kocaeli Üniversitesi Bilgisayar Mühendisliği dersi kapsamında C programlama dili kullanılarak geliştirilmiş, iki farklı ırkın (İnsan İmparatorluğu ve Ork Lejyonu) yer aldığı ızgara tabanlı bir strateji oyunu simülasyonudur. [cite: 3, 6, 7]

[cite_start]Projenin temel amacı, karmaşık algoritmalarla hesaplanan mantıksal olayların savaşın dinamiklerini nasıl etkilediğini kullanıcıya açık bir şekilde göstermektir. [cite: 17]

## ✨ Temel Özellikler ve Savaş Mekaniği

* [cite_start]**Izgara Tabanlı Savaş Alanı:** Savaş, birimlerin, kahramanların ve canavarların stratejik önem taşıdığı ızgara tabanlı bir haritada gerçekleşir. [cite: 7, 18]
* [cite_start]**Detaylı Savaş Hesaplamaları:** Savaş sırasında birimlerin saldırı, savunma, sağlık, kritik vuruş ve yorgunluk gibi faktörlere dayalı olarak hesaplamalar yapılır. [cite: 9, 22]
* [cite_start]**Eş Zamanlı Saldırı Sistemi:** Birimler aynı anda saldırı yapar ve hasar miktarı, savunma gücü, birlik sayısı ve birim türlerine göre hesaplanır. [cite: 12]
* [cite_start]**Kritik Vuruşlar ve Yorgunluk:** Kritik vuruşlar belirli sayıda saldırı sonrası etkinleşerek savaşın akışını değiştirir[cite: 13]. [cite_start]Yorgunluk etkeni ise her adımda birliklerin saldırı gücünü %10 düşürür. [cite: 59]
* [cite_start]**JSON Veri İşleme:** Simülasyon, birim, kahraman ve canavar bilgilerini içeren JSON dosyalarından alınan verilerin işlenmesiyle gerçekleşir. [cite: 10, 21]
* **Görselleştirme:** SDL2 kütüphanesi kullanılarak, savaşın başlangıç ve bitiş anları görselleştirilir. [cite_start]Can barları ve birlik sayıları ekranda gösterilir. [cite: 62, 63, 70, 80]
* [cite_start]**Orijinal Müzik ve Ambiyans:** Savaş ortamına uygun, tamamen özgün müzikler (FL STUDIO 2024 ile yapıldı) ve kullanıcı dostu bir arayüz ile zenginleştirilmiş bir ambiyans oluşturulmuştur. [cite: 24, 87, 105, 106]

## 🛠️ Kullanılan Teknolojiler

* [cite_start]**Programlama Dili:** C [cite: 6]
* [cite_start]**Görselleştirme Kütüphaneleri:** SDL2, SDL_ttf, SDL2_image [cite: 63]
* [cite_start]**Veri Çekme:** cURL Kütüphanesi (Senaryo verilerini internetten çekmek için) [cite: 96]
* [cite_start]**Müzik Yapımı:** FL STUDIO 2024 [cite: 105]
* [cite_start]**Görsel Tasarım:** Artbreeder (Karakter tasarımı için) [cite: 103][cite_start], Adobe Photoshop (Arka plan ve detay silme) [cite: 104]

## 💻 Kurulum ve Çalıştırma

Bu proje C dilinde yazılmış bir simülasyon olduğundan, çalıştırmak için uygun bir C derleyicisine (örneğin GCC) ve kullanılan kütüphanelere ihtiyacınız olacaktır.

1.  **Depoyu Klonlayın:**
    ```bash
    git clone [depo-adresiniz]
    cd [depo-adiniz]
    ```
2.  **Kütüphaneleri Kurun:** Projenin başarılı bir şekilde derlenmesi için **SDL2**, **SDL2_image**, **SDL2_ttf** ve **cURL** kütüphanelerinin sisteminizde kurulu ve projeye bağlı olması gerekir.
3.  **Derleme:**
    ```bash
    # Örnek GCC komutu, kütüphane bağlama ayarları sisteminize göre değişebilir.
    gcc main.c -o SavasSimulasyonu -lSDL2 -lSDL2_image -lSDL2_ttf -lcurl
    ```
4.  **Çalıştırma:**
    ```bash
    ./SavasSimulasyonu
    ```
    * (Program sizden bir senaryo numarası seçmenizi isteyecektir.) [cite: 99]
    * Simülasyonun başlaması için `ENTER` tuşuna basın. [cite: 89]

## 📊 Deneyimsel Sonuçlar

[cite_start]Simülasyon, kullanıcıya savaşın başlangıç ve bitiş anlarının görsel bir temsilini sunar. [cite: 25]

### Savaş Öncesi Durum
Tüm birliklerin can barları %100 doludur. [cite_start]Sol/sağ üstte kahramanlar, sol/sağ altta ise canavarlar görünmektedir. [cite: 109, 110]

### Savaş Sonrası Durum
Simülasyon tamamlandığında, can barlarında azalma görülür ve canı tamamen biten birlikler görsel olarak oyun sahasından kaldırılır. [cite_start]Aşağıdaki görselde İnsan İmparatorluğu'nun savaşı kazandığı senaryo sonucu gösterilmektedir. [cite: 111, 112]

## ✍️ Yazar Katkıları

| Geliştirici | Katkı Alanı |
| :--- | :--- |
| **Çağatay ALTINTOPAÇ** | [cite_start]Veri Çekme, Ayrıştırma, Savaş Mekaniği Yansıtılması, Oyun Müzikleri, Photoshop işlemleri. [cite: 124, 127] |
| **Ali KILINÇ** | [cite_start]Verilerin Görselleştirilmesi, Izgara Düzeninin Sağlanması, Senaryo Verilerinin İnternetten Çekilmesi (cURL), Kodun Son Düzeni ve Okunabilirliği. [cite: 125, 127] |

---
