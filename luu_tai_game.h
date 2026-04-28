#ifndef LUU_TAI_GAME_H
#define LUU_TAI_GAME_H

#include "cau_truc_du_lieu.h"

/*
 * Lưu ván cờ đang chơi xuống file.
 * Trả về: 1 nếu lưu thành công, 0 nếu thất bại
 */
int luu_van_co(const TrangThaiVanCo *trang_thai, const char *ten_file);

/*
 * Tải lại ván cờ đã lưu từ file.
 * Trả về: 1 nếu tải thành công, 0 nếu thất bại
 */
int tai_van_co(TrangThaiVanCo *trang_thai, const char *ten_file);

/*
 * Kiểm tra xem có file lưu tồn tại không.
 * Trả về: 1 nếu có, 0 nếu không
 */
int kiem_tra_co_file_luu(const char *ten_file);

/*
 * Xóa file lưu (sau khi ván cờ kết thúc).
 * Trả về: 1 nếu xóa thành công, 0 nếu thất bại
 */
int xoa_file_luu(const char *ten_file);

/*
 * In thông tin tóm tắt của ván cờ đã lưu.
 * Dùng để hiển thị "Có ván cờ đang dở..." trước khi hỏi người dùng.
 */
void in_thong_tin_file_luu(const char *ten_file);

#endif /* LUU_TAI_GAME_H */
