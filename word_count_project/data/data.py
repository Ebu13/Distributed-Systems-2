import random
from lorem import paragraph

# 150.000 kelimelik rastgele metin oluşturma
word_count = 150000  # 150.000 kelime
random_text = []

# Metni küçük paragraflar halinde oluşturalım
while len(" ".join(random_text).split()) < word_count:
    random_text.append(paragraph())

# Listeyi birleştirip UTF-8 formatında dosyaya yazma
with open("text.txt", "w", encoding="utf-8") as file:
    file.write("\n".join(random_text))

print("text.txt dosyasına 150.000 kelimelik metin yazıldı.")
