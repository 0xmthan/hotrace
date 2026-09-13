#ifndef HOTRACE_H
#define HOTRACE_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>


// read syscall için kritik performans
// Max Linux pipe kapasitesi ve L1 Cache uyumu (64KB)

# define READ_SIZE      65536      // Tek read() çağrısının boyutu
# define POOL_SIZE      65536      // Bir struct havuzundaki t_item sayısı
# define CHUNK_SIZE     8388608    // Bir string chunk'ının boyutu (8 MB)
# define TABLE_SIZE     131072     // Hash tablosu boyutu (2'nin kuvveti olmalı)

// 1MB = 1024 KB
// 1KB = 1024 Byte
// 64KB = 65536 Byte
// 8MB = 8388608 Byte

// Key-Value struct'ı
typedef struct s_item
{
	char			*key;
	char			*value;

	// Aranan key' bu key ile eşleşmiyorsa
	// collasion(çakışma) vardır, o yüzden next'e bakıp key 
	// eşleşmesi kontrol edilir.
	struct s_item	*next; 
}	t_item;


// Key-Value Pair Array'i
// Her bir t_item için malloc açmak yerine büyük bir yer açıp
// offset kaydırarak t_item'ları yerleştiriyoruz, ve malloc çağrılarını en aza indiriyoruz.

typedef struct s_pool
{
	t_item			nodes[POOL_SIZE];
	int				current_index;
	struct s_pool	*next;
}	t_pool;


// Her key-value okuma sonrası malloc ile yeni yer açmak yerine
// Tek malloc ile her read de offset kaydırarak veriyi set ediyoruz.
// Her \n görülen yeri \0 yapıp aynı zamanda offset'i de key-value adresi 
// olarak verip ilerliyoruz.

typedef struct s_chunk
{
	char			*data;		// malloc(CHUNK_SIZE)
	size_t			offset;		// bu chunk'ta ne kadar dolu
	struct s_chunk	*next;		// chunk dolarsa açılan yeni blok
}	t_chunk;


// Her şeyi bir arada tutan ana context

typedef struct s_hotrace
{
	t_item			*table[TABLE_SIZE];	// hash tablosu (bucket array)
	t_pool			*pool_head;			// free için baştan takip
	t_pool			*pool_curr;			// aktif yazılan havuz
	t_chunk			*chunk_head;		// free için baştan takip
	t_chunk			*chunk_curr;		// aktif yazılan chunk
}	t_hotrace;


// utils
size_t	ft_strlen(const char *str);
void	ft_putendl(const char *str);
bool	ft_strcmp(const char* s1, const char* s2);


#endif

