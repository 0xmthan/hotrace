import random
import string
import sys

def get_random_string(length=10):
    return ''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase + string.digits, k=length))

def generate_test(num_pairs, filename="test_data.txt"):
    keys = []
    
    with open(filename, 'w') as f:
        # Key-Value çiftlerini üret ve dosyaya yaz
        for _ in range(num_pairs):
            key = get_random_string(random.randint(5, 15))
            value = get_random_string(random.randint(5, 20))
            keys.append(key)
            f.write(f"{key}\n{value}\n")
        
        # Hotrace ayracı (Boş satır)
        f.write("\n")
        
        # Arama (Search) bölümü
        # %80 var olan kelimelerden, %20 rastgele (bulunamayacak) kelimelerden sor
        for _ in range(num_pairs):
            if random.random() < 0.8:
                f.write(f"{random.choice(keys)}\n")
            else:
                f.write(f"{get_random_string(12)}\n")
                
    print(f"Test dosyasi '{filename}' {num_pairs} adet cift ile olusturuldu.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Kullanim: python3 generator.py <cift_sayisi>")
        sys.exit(1)
    generate_test(int(sys.argv[1]))
