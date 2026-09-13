import random
import string
import sys

def get_random_string(min_len, max_len):
    length = random.randint(min_len, max_len)
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def generate_stress_test(num_pairs, filename="huge_test.txt"):
    keys = []
    
    print(f"[{num_pairs} kayit] Veriler uretiliyor, lutfen bekleyin...")
    
    with open(filename, 'w') as f:
        # 1. BÖLÜM: KEY-VALUE EKLEME (STORE)
        for i in range(num_pairs):
            # Çeşitlilik: Bazıları çok kısa, bazıları çok uzun
            if i % 10 == 0:
                key = get_random_string(50, 100) # Uzun key
            else:
                key = get_random_string(3, 10)   # Kısa key
                
            value = get_random_string(5, 20)
            
            # Key'leri sonradan aramak için bellekte tutuyoruz
            keys.append(key)
            
            f.write(f"{key}\n{value}\n")
            
            if i > 0 and i % (num_pairs // 10) == 0:
                print(f"Yaziliyor... %{int((i/num_pairs)*100)}")
        
        # 2. BÖLÜM: AYIRICI
        f.write("\n")
        
        # 3. BÖLÜM: ARAMA (SEARCH)
        print("Arama satirlari uretiliyor...")
        # Arama sayısını, eklenen veri sayısının 1.5 katı yapalım ki sistem yorulsun
        search_count = int(num_pairs * 1.5) 
        
        for i in range(search_count):
            chance = random.random()
            if chance < 0.70:
                # %70 ihtimalle var olan bir kelime sor (Bulunacak)
                f.write(f"{random.choice(keys)}\n")
            else:
                # %30 ihtimalle rastgele uydurma bir kelime sor (Not found.)
                f.write(f"{get_random_string(5, 15)}\n")
                
    print(f"\nBasarili! '{filename}' dosyasi olusturuldu.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Kullanim: python3 huge_generator.py <kayit_sayisi>")
        print("Ornek: python3 huge_generator.py 5000000")
        sys.exit(1)
    
    try:
        count = int(sys.argv[1])
        generate_stress_test(count)
    except ValueError:
        print("Lutfen gecerli bir sayi girin.")
