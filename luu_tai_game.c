#include "luu_tai_game.h"

/* ================================================================
 * luu_tai_game.c — Thành viên B
 * Chức năng: Lưu và tải ván cờ bằng file nhị phân
 * ================================================================ */

/* ---------- HÀM NỘI BỘ (chỉ dùng trong file này) ---------- */

// Kiểm tra chữ nhận diện "CARO" — xác nhận file hợp lệ
static int kiem_tra_chu_nhan_dien(const TrangThaiVanCo *trang_thai) {
    return (trang_thai->chu_nhan_dien[0] == 'C' &&
            trang_thai->chu_nhan_dien[1] == 'A' &&
            trang_thai->chu_nhan_dien[2] == 'R' &&
            trang_thai->chu_nhan_dien[3] == 'O');
}

/* ---------- HÀM CÔNG KHAI ---------- */

/*
 * luu_van_co — Lưu toàn bộ trạng thái ván cờ xuống file nhị phân
 *
 * Cách hoạt động:
 *   fopen  → mở file để ghi
 *   fwrite → sao chép toàn bộ struct từ RAM xuống file
 *   fclose → đóng file
 */
int luu_van_co(const TrangThaiVanCo *trang_thai, const char *ten_file) {
    if (trang_thai == NULL || ten_file == NULL) {
        fprintf(stderr, "[Luu game] Loi: thieu thong tin dau vao\n");
        return 0;
    }

    // Mở file để ghi nhị phân ("wb" = write binary)
    FILE *file = fopen(ten_file, "wb");
    if (file == NULL) {
        fprintf(stderr, "[Luu game] Loi: khong mo duoc file '%s'\n", ten_file);
        return 0;
    }

    // Tạo bản sao để điền thời gian lưu mà không sửa bản gốc
    TrangThaiVanCo ban_sao = *trang_thai;
    ban_sao.chu_nhan_dien[0] = 'C';
    ban_sao.chu_nhan_dien[1] = 'A';
    ban_sao.chu_nhan_dien[2] = 'R';
    ban_sao.chu_nhan_dien[3] = 'O';
    ban_sao.phien_ban    = 1;
    ban_sao.thoi_gian_luu = time(NULL);     // ghi thời điểm lưu

    // Ghi toàn bộ struct xuống file một lần duy nhất
    size_t so_phan_tu_da_ghi = fwrite(&ban_sao, sizeof(TrangThaiVanCo), 1, file);
    fclose(file);

    if (so_phan_tu_da_ghi != 1) {
        fprintf(stderr, "[Luu game] Loi: ghi file that bai\n");
        return 0;
    }

    printf("[Luu game] Da luu van co vao '%s'\n", ten_file);
    return 1;
}

/*
 * tai_van_co — Tải trạng thái ván cờ từ file nhị phân về RAM
 *
 * Cách hoạt động:
 *   fopen  → mở file để đọc
 *   fread  → sao chép từ file vào RAM (ngược với fwrite)
 *   fclose → đóng file
 *   Kiểm tra chữ "CARO" → xác nhận file đúng loại
 */
int tai_van_co(TrangThaiVanCo *trang_thai, const char *ten_file) {
    if (trang_thai == NULL || ten_file == NULL) {
        fprintf(stderr, "[Tai game] Loi: thieu thong tin dau vao\n");
        return 0;
    }

    // Mở file để đọc nhị phân ("rb" = read binary)
    FILE *file = fopen(ten_file, "rb");
    if (file == NULL) {
        fprintf(stderr, "[Tai game] Loi: khong tim thay file '%s'\n", ten_file);
        return 0;
    }

    // Đọc toàn bộ struct từ file vào biến tạm
    TrangThaiVanCo du_lieu_tam;
    size_t so_phan_tu_da_doc = fread(&du_lieu_tam, sizeof(TrangThaiVanCo), 1, file);
    fclose(file);

    if (so_phan_tu_da_doc != 1) {
        fprintf(stderr, "[Tai game] Loi: file bi hong\n");
        return 0;
    }

    // Kiểm tra chữ nhận diện — đảm bảo đây là file save game
    if (!kiem_tra_chu_nhan_dien(&du_lieu_tam)) {
        fprintf(stderr, "[Tai game] Loi: day khong phai file save game hop le\n");
        return 0;
    }

    // Kiểm tra phiên bản
    if (du_lieu_tam.phien_ban != 1) {
        fprintf(stderr, "[Tai game] Loi: phien ban file khong tuong thich\n");
        return 0;
    }

    // Gán dữ liệu vào con trỏ được truyền vào
    *trang_thai = du_lieu_tam;

    printf("[Tai game] Da tai van co: %s vs %s (%d nuoc di)\n",
           trang_thai->nguoi_choi_1.ten,
           trang_thai->nguoi_choi_2.ten,
           trang_thai->so_nuoc_da_di);
    return 1;
}

/*
 * kiem_tra_co_file_luu — Kiểm tra file lưu có tồn tại không
 */
int kiem_tra_co_file_luu(const char *ten_file) {
    FILE *file = fopen(ten_file, "rb");
    if (file == NULL) return 0;
    fclose(file);
    return 1;
}

/*
 * xoa_file_luu — Xóa file lưu khỏi ổ cứng
 */
int xoa_file_luu(const char *ten_file) {
    if (remove(ten_file) == 0) {
        printf("[Luu game] Da xoa file luu '%s'\n", ten_file);
        return 1;
    }
    fprintf(stderr, "[Luu game] Loi: khong xoa duoc file '%s'\n", ten_file);
    return 0;
}

/*
 * in_thong_tin_file_luu — Hiển thị tóm tắt ván cờ đã lưu
 */
void in_thong_tin_file_luu(const char *ten_file) {
    TrangThaiVanCo du_lieu_tam;

    FILE *file = fopen(ten_file, "rb");
    if (file == NULL) { printf("Khong co file luu.\n"); return; }

    size_t ket_qua_doc = fread(&du_lieu_tam, sizeof(TrangThaiVanCo), 1, file);
    fclose(file);

    if (ket_qua_doc != 1 || !kiem_tra_chu_nhan_dien(&du_lieu_tam)) {
        printf("File luu bi hong.\n");
        return;
    }

    // Chuyển thời gian lưu sang dạng chữ dễ đọc
    char chuoi_thoi_gian[64];
    struct tm *thoi_gian = localtime(&du_lieu_tam.thoi_gian_luu);
    strftime(chuoi_thoi_gian, sizeof(chuoi_thoi_gian), "%d/%m/%Y %H:%M", thoi_gian);

    printf("+------------------------------------------+\n");
    printf("|          VAN CO DANG DO                  |\n");
    printf("+------------------------------------------+\n");
    printf("| Nguoi choi 1 : %-25s|\n", du_lieu_tam.nguoi_choi_1.ten);
    printf("| Nguoi choi 2 : %-25s|\n", du_lieu_tam.nguoi_choi_2.ten);
    printf("| So nuoc da di: %-25d|\n", du_lieu_tam.so_nuoc_da_di);
    printf("| Luot hien tai: %-25c|\n", du_lieu_tam.luot_hien_tai);
    printf("| Thoi gian luu: %-25s|\n", chuoi_thoi_gian);
    printf("+------------------------------------------+\n");
}
