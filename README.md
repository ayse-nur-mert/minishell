# Minishell - 42 School Project

## 📋 Proje Hakkında

Minishell, UNIX shell'inin basitleştirilmiş bir versiyonudur. Bu proje, sistem programlama, süreç yönetimi, dosya tanımlayıcıları ve Unix sistem çağrıları hakkında derinlemesine bilgi edinmeyi amaçlar.

## 🎯 Proje Amaçları

- **Shell Temelleri**: Unix shell'inin nasıl çalıştığını anlama
- **Sözdizimi Analizi**: Komutların doğru sözdizimi ile analiz edilmesi
- **Lexical Analysis**: Kullanıcı girdilerinin token'lara ayrıştırılması
- **Çevre Değişkenleri**: Environment variable yönetimi
- **Bellek Yönetimi**: Dinamik bellek yönetimi ve bellek sızıntılarının önlenmesi

## 🏗️ Proje Yapısı

```
minishell/
├── Makefile                # Derleme kuralları
├── README.md              # Bu dosya
├── minishell             # Derlenmiş program
├── lib/                  # Kütüphaneler
│   ├── minishell.h       # Ana header dosyası
│   └── libft/           # Libft kütüphanesi
├── obj/                  # Object dosyaları
└── src/                 # Kaynak kodlar
    ├── main.c           # Ana program entry point
    ├── shell_core.c     # Shell ana döngüsü ve işleme
    ├── env_*.c          # Environment değişken yönetimi
    ├── token_*.c        # Token operasyonları ve bellek yönetimi
    ├── lexer.c          # Lexical analysis ve tokenization
    ├── lexer_utils.c    # Lexer yardımcı fonksiyonları  
    ├── syntax_*.c       # Sözdizimi kontrolü ve validasyon
    └── expansion_utils.c # Değişken genişletme ve quote handling
```

## 🔧 Derleme ve Kullanım

### Derleme
```bash
make
```

### Temizleme
```bash
make clean  # Object dosyalarını sil
make fclean # Tüm üretilen dosyaları sil
make re     # Yeniden derle
```

### Çalıştırma
```bash
./minishell
```

## 📚 Fonksiyon Referansı

### 🎮 Ana Shell Fonksiyonları

#### `void init_shell(t_shell *shell, char **envp)`
Shell yapısını başlatır ve çevre değişkenlerini yükler.
- **Parametreler**: Shell yapısı ve çevre değişkenleri
- **Fonksiyon**: Shell'i çalışmaya hazır hale getirir

#### `void shell_loop(t_shell *shell)`
Ana shell döngüsü. Kullanıcı girişi alır ve işler.
- **Parametreler**: Shell yapısı
- **Fonksiyon**: Sürekli kullanıcı girişi bekler ve işler

#### `void cleanup_shell(t_shell *shell)`
Shell kapatıldığında bellek temizliği yapar.
- **Parametreler**: Shell yapısı
- **Fonksiyon**: Bellek sızıntılarını önler

---

### 🔍 Sözdizimi Doğrulama

#### `int validate_syntax(char *input)`
Kullanıcı girişinin sözdizimi doğruluğunu kontrol eder.
- **Parametreler**: Kullanıcı girişi
- **Dönüş**: SUCCESS (0) veya FAILURE (1)

#### `int check_quote_matching(char *input)`
Tırnak işaretlerinin doğru kapatılıp kapatılmadığını kontrol eder.
- **Parametreler**: Kullanıcı girişi
- **Dönüş**: SUCCESS veya FAILURE

#### `int check_operator_syntax(char *input)`
Operatörlerin (|, <, >) doğru kullanılıp kullanılmadığını kontrol eder.
- **Parametreler**: Kullanıcı girişi
- **Dönüş**: SUCCESS veya FAILURE

#### `int check_empty_segments(char *input)`
Pipe'lar arasında boş komut segmentlerini kontrol eder.
- **Parametreler**: Kullanıcı girişi
- **Dönüş**: SUCCESS veya FAILURE

#### `void print_syntax_error(char *error_msg, int position)`
Sözdizimi hatalarını kullanıcıya bildirir.
- **Parametreler**: Hata mesajı ve pozisyon
- **Fonksiyon**: Hatayı terminale yazdırır

---

### 🌍 Çevre Değişkeni Yönetimi

#### `t_env *create_env_node(char *key, char *value)`
Yeni bir çevre değişkeni düğümü oluşturur.
- **Parametreler**: Anahtar ve değer
- **Dönüş**: Yeni env düğümü veya NULL

#### `void add_env_node(t_env **env, t_env *new_node)`
Çevre değişkenleri listesine yeni düğüm ekler.
- **Parametreler**: Env listesi ve yeni düğüm
- **Fonksiyon**: Liste sonuna ekler

#### `t_env *find_env_node(t_env *env, char *key)`
Belirtilen anahtara sahip düğümü bulur.
- **Parametreler**: Env listesi ve anahtar
- **Dönüş**: Bulunan düğüm veya NULL

#### `int remove_env_node(t_env **env, char *key)`
Belirtilen anahtara sahip düğümü siler.
- **Parametreler**: Env listesi ve anahtar
- **Dönüş**: SUCCESS veya FAILURE

#### `char *get_env_value(t_env *env, char *key)`
Çevre değişkeninin değerini alır.
- **Parametreler**: Env listesi ve anahtar
- **Dönüş**: Değer string'i veya NULL

#### `int set_env_value(t_env **env, char *key, char *value)`
Çevre değişkenini ayarlar veya günceller.
- **Parametreler**: Env listesi, anahtar ve değer
- **Dönüş**: SUCCESS veya FAILURE

#### `int unset_env_value(t_env **env, char *key)`
Çevre değişkenini siler.
- **Parametreler**: Env listesi ve anahtar
- **Dönüş**: SUCCESS veya FAILURE

#### `int env_key_exists(t_env *env, char *key)`
Çevre değişkeninin var olup olmadığını kontrol eder.
- **Parametreler**: Env listesi ve anahtar
- **Dönüş**: 1 (var) veya 0 (yok)

#### `void free_env_node(t_env *node)`
Tek bir env düğümünü serbest bırakır.
- **Parametreler**: Env düğümü
- **Fonksiyon**: Belleği serbest bırakır

#### `void free_env_list(t_env *env)`
Tüm env listesini serbest bırakır.
- **Parametreler**: Env listesi
- **Fonksiyon**: Tüm belleği temizler

#### `int count_env_nodes(t_env *env)`
Env düğümlerinin sayısını döndürür.
- **Parametreler**: Env listesi
- **Dönüş**: Düğüm sayısı

#### `char **env_to_array(t_env *env)`
Env listesini array formatına çevirir.
- **Parametreler**: Env listesi
- **Dönüş**: String array veya NULL

#### `t_env *init_env_from_system(char **envp)`
Sistem çevre değişkenlerinden env listesi oluşturur.
- **Parametreler**: Sistem env array'i
- **Dönüş**: Yeni env listesi

---

### 🔤 Lexical Analysis (Tokenization)

#### `int is_whitespace(char c)`
Karakterin boşluk olup olmadığını kontrol eder.
- **Parametreler**: Karakter
- **Dönüş**: 1 (boşluk) veya 0

#### `int is_quote(char c)`
Karakterin tırnak işareti olup olmadığını kontrol eder.
- **Parametreler**: Karakter
- **Dönüş**: 1 (tırnak) veya 0

#### `int is_operator_char(char c)`
Karakterin operatör olup olmadığını kontrol eder.
- **Parametreler**: Karakter
- **Dönüş**: 1 (operatör) veya 0

#### `int is_token_separator(char c)`
Karakterin token ayırıcı olup olmadığını kontrol eder.
- **Parametreler**: Karakter
- **Dönüş**: 1 (ayırıcı) veya 0

#### `int skip_whitespace(const char *str, int *i)`
String'de boşlukları atlar.
- **Parametreler**: String ve pozisyon pointer'ı
- **Dönüş**: 1 (boşluk atlandı) veya 0

#### `int is_token_char(char c)`
Karakterin token parçası olup olmadığını kontrol eder.
- **Parametreler**: Karakter
- **Dönüş**: 1 (token parçası) veya 0

---

### 🎯 Token Yönetimi

#### `t_token *create_token_node(char *content, e_token_types type)`
Yeni bir token düğümü oluşturur.
- **Parametreler**: İçerik ve token tipi
- **Dönüş**: Yeni token veya NULL

#### `void add_token_node(t_token **tokens, t_token *new_token)`
Token listesine yeni token ekler.
- **Parametreler**: Token listesi ve yeni token
- **Fonksiyon**: Liste sonuna ekler

#### `t_token *find_token_by_type(t_token *tokens, e_token_types type)`
Belirtilen tipteki ilk token'ı bulur.
- **Parametreler**: Token listesi ve tip
- **Dönüş**: Bulunan token veya NULL

#### `t_token *get_last_token(t_token *tokens)`
Listedeki son token'ı döndürür.
- **Parametreler**: Token listesi
- **Dönüş**: Son token veya NULL

#### `int remove_token_node(t_token **tokens, t_token *token_to_remove)`
Belirtilen token'ı listeden siler.
- **Parametreler**: Token listesi ve silinecek token
- **Dönüş**: SUCCESS veya FAILURE

#### `void free_token_node(t_token *token)`
Tek bir token'ı serbest bırakır.
- **Parametreler**: Token
- **Fonksiyon**: Belleği serbest bırakır

#### `void free_tokens(t_token *tokens)`
Tüm token listesini serbest bırakır.
- **Parametreler**: Token listesi
- **Fonksiyon**: Tüm belleği temizler

#### `int count_tokens(t_token *tokens)`
Token sayısını döndürür.
- **Parametreler**: Token listesi
- **Dönüş**: Token sayısı

#### `int count_tokens_by_type(t_token *tokens, e_token_types type)`
Belirtilen tipteki token sayısını döndürür.
- **Parametreler**: Token listesi ve tip
- **Dönüş**: Token sayısı

#### `t_token *duplicate_token_list(t_token *tokens)`
Token listesinin kopyasını oluşturur.
- **Parametreler**: Token listesi
- **Dönüş**: Yeni token listesi

#### `int is_redirect_token(e_token_types type)`
Token'ın yönlendirme operatörü olup olmadığını kontrol eder.
- **Parametreler**: Token tipi
- **Dönüş**: 1 (yönlendirme) veya 0

#### `int is_operator_token(e_token_types type)`
Token'ın operatör olup olmadığını kontrol eder.
- **Parametreler**: Token tipi
- **Dönüş**: 1 (operatör) veya 0

#### `t_token *get_next_word_token(t_token *token)`
Belirtilen token'dan sonraki ilk kelime token'ını bulur.
- **Parametreler**: Başlangıç token'ı
- **Dönüş**: Bulunan token veya NULL

#### `t_token *get_prev_word_token(t_token *token)`
Belirtilen token'dan önceki ilk kelime token'ını bulur.
- **Parametreler**: Başlangıç token'ı
- **Dönüş**: Bulunan token veya NULL

#### `int validate_token_sequence(t_token *tokens)`
Token diziliminin sözdizimi kurallarına uygunluğunu kontrol eder.
- **Parametreler**: Token listesi
- **Dönüş**: SUCCESS veya FAILURE

#### `t_token *tokenize(char *input)`
Kullanıcı girişini token'lara ayrıştırır.
- **Parametreler**: Kullanıcı girişi
- **Dönüş**: Token listesi veya NULL

---

### 📈 Değişken Genişletme (Variable Expansion)

#### `char *handle_special_vars(char *name, t_shell *shell)`
Özel shell değişkenlerini ($?, $$, $0) işler.
- **Parametreler**: Değişken adı ve shell yapısı
- **Dönüş**: Genişletilmiş değer veya NULL
- **Desteklenen Özel Değişkenler**:
  - `$?`: Son komutun exit status'u
  - `$$`: Shell'in process ID'si
  - `$0`: Shell'in adı (minishell)

#### `char *expand_variable(char *var, t_shell *shell)`
Bir değişkeni genişletir (env veya özel değişken).
- **Parametreler**: Değişken adı ve shell yapısı
- **Dönüş**: Genişletilmiş değer
- **Fonksiyon**: Önce özel değişkenleri, sonra environment değişkenlerini kontrol eder

#### `char *expand_variables_in_string(char *str, t_shell *shell)`
String içindeki tüm değişkenleri genişletir (temel versiyon).
- **Parametreler**: Kaynak string ve shell yapısı
- **Dönüş**: Genişletilmiş string
- **Fonksiyon**: String içindeki `$variable` ifadelerini değerleriyle değiştirir

#### `char *expand_variables_in_string_quoted(char *str, t_shell *shell)`
Quote-aware değişken genişletme fonksiyonu.
- **Parametreler**: Kaynak string ve shell yapısı
- **Dönüş**: Genişletilmiş string
- **Özellikler**:
  - Single quote içinde değişken genişletme yapmaz (`'$HOME'` → `$HOME`)
  - Double quote içinde değişken genişletme yapar (`"$HOME"` → `/home/user`)
  - Escape edilmiş değişkenleri genişletmez (`\$HOME` → `$HOME`)

#### `t_token *tokenize_with_expansion(char *input, t_shell *shell)`
Tokenize işlemi sırasında değişken genişletme yapar.
- **Parametreler**: Giriş string'i ve shell yapısı
- **Dönüş**: Genişletilmiş token listesi
- **Fonksiyon**: 
  - Önce normal tokenize işlemi yapar
  - Sonra her TOKEN_WORD tipindeki token'da `$` varsa genişletme yapar
  - Quote kurallarına uygun şekilde genişletme yapar

#### Genişletme Kuralları
1. **Single Quotes (`'...'`)**: Hiçbir genişletme yapılmaz
2. **Double Quotes (`"..."`)**: Değişken genişletme yapılır
3. **Escape (`\$`)**: Genişletme yapılmaz
4. **Tanımsız Değişkenler**: Boş string olarak değiştirilir
5. **Özel Karakterler**: Sadece alphanumeric ve `_` karakterleri değişken adında kabul edilir

---

### 🛠️ Yardımcı Fonksiyonlar

#### `int is_builtin(char *cmd)`
Komutun built-in olup olmadığını kontrol eder.
- **Parametreler**: Komut adı
- **Dönüş**: 1 (built-in) veya 0

#### `void print_error(char *message)`
Hata mesajını yazdırır.
- **Parametreler**: Hata mesajı
- **Fonksiyon**: Mesajı stderr'e yazdırır

#### `char *ft_strndup(const char *s, size_t n)`
String'in belirli uzunluktaki kopyasını oluşturur.
- **Parametreler**: Kaynak string ve uzunluk
- **Dönüş**: Yeni string veya NULL

## 📁 Veri Yapıları

### `typedef struct s_env`
Çevre değişkenleri için bağlı liste düğümü.
```c
typedef struct s_env
{
    char            *key;    // Değişken adı
    char            *value;  // Değişken değeri
    struct s_env    *next;   // Sonraki düğüm
}   t_env;
```

### `typedef struct s_token`
Token'lar için çift bağlı liste düğümü.
```c
typedef struct s_token
{
    char            *content;  // Token içeriği
    e_token_types   type;      // Token tipi
    struct s_token  *prev;     // Önceki düğüm
    struct s_token  *next;     // Sonraki düğüm
}   t_token;
```

### `typedef struct s_shell`
Ana shell yapısı.
```c
typedef struct s_shell
{
    t_env   *env;          // Çevre değişkenleri
    int     exit_status;   // Son komutun çıkış durumu
}   t_shell;
```

### `typedef enum e_token_types`
Token türleri.
```c
typedef enum e_token_types
{
    TOKEN_NONE,         // Belirsiz
    TOKEN_WORD,         // Kelime
    TOKEN_COMMAND,      // Komut
    TOKEN_ARGUMENT,     // Argüman
    TOKEN_FILE,         // Dosya
    TOKEN_PIPE,         // Pipe (|)
    TOKEN_REDIRECT_IN,  // Girdi yönlendirme (<)
    TOKEN_REDIRECT_OUT, // Çıktı yönlendirme (>)
    TOKEN_APPEND,       // Ekle yönlendirme (>>)
    TOKEN_HEREDOC       // Here document (<<)
} e_token_types;
```

## 🎯 Mevcut Özellikler

- ✅ **Sözdizimi Doğrulama**: Tırnak eşleştirme, operatör kontrolü
- ✅ **Lexical Analysis**: Token'lara ayrıştırma
- ✅ **Çevre Değişken Yönetimi**: Tam CRUD operasyonları
- ✅ **Bellek Yönetimi**: Sızıntı önleme ve temizlik
- ✅ **Değişken Genişletme**: 
  - Özel değişkenler (`$?`, `$$`, `$0`)
  - Environment değişkenleri (`$HOME`, `$USER`, vb.)
  - Quote-aware genişletme (single/double quote desteği)
  - Escape character desteği (`\$`)
- ✅ **Quote Handling**:
  - Single quotes: Değişken genişletme yapılmaz
  - Double quotes: Değişken genişletme yapılır
  - Mixed quote desteği
- ✅ **Tokenization with Expansion**: Token seviyesinde değişken genişletme

## 🔍 Desteklenen Değişken Genişletme Örnekleri

```bash
# Environment değişkenleri
echo $HOME          # /home/user
echo $USER          # kullanici_adi

# Özel değişkenler  
echo $?             # Son komutun exit status'u
echo $$             # Shell'in process ID'si
echo $0             # minishell

# Quote handling
echo '$HOME'        # $HOME (genişletme yapılmaz)
echo "$HOME"        # /home/user (genişletme yapılır)
echo \$HOME         # $HOME (escape edilmiş)

# Mixed quotes
echo "User: $USER, Home: '$HOME'"  # User: john, Home: '$HOME'
```

## 🚧 Geliştirme Durumu

Bu proje şu anda **lexical analysis** ve **syntax validation** aşamalarında tamamlanmıştır. Gelecek adımlar:

1. **Parsing**: AST (Abstract Syntax Tree) oluşturma
2. **Command Execution**: Komut çalıştırma
3. **Built-in Commands**: cd, echo, env, export, unset, exit
4. **Redirection**: Dosya yönlendirme işlemleri
5. **Pipes**: Pipe operatörü implementasyonu

## 🤝 Katkıda Bulunma

Bu proje 42 School müfredatının bir parçasıdır. Eğitim amaçlı geliştirilmiştir.

## 📝 Lisans

Bu proje 42 School kuralları çerçevesinde geliştirilmiştir.

---

**Not**: Bu README, projenin mevcut durumunu yansıtmaktadır. Proje geliştikçe güncellenecektir.
