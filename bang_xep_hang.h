#ifndef BANG_XEP_HANG_H
#define BANG_XEP_HANG_H

#include "cau_truc_du_lieu.h"

/*
 * Cập nhật kết quả sau mỗi ván cờ.
 *   ten_nguoi_thang - tên người thắng (NULL nếu hòa)
 *   ten_nguoi_thua  - tên người thua  (NULL nếu hòa)
 *   ten_nguoi_choi_1, ten_nguoi_choi_2 - dùng khi hòa
 *   la_hoa          - 1 nếu ván hòa, 0 nếu có người thắng
 */
void cap_nhat_ket_qua(const char *ten_nguoi_thang,
                      const char *ten_nguoi_thua,
                      const char *ten_nguoi_choi_1,
                      const char *ten_nguoi_choi_2,
                      int la_hoa);

/*
 * Đọc file và in bảng xếp hạng ra màn hình.
 * Danh sách sắp xếp theo tỷ lệ thắng từ cao xuống thấp.
 */
void hien_thi_bang_xep_hang(void);

/*
 * Tìm hồ sơ của một người chơi theo tên.
 * Trả về: 1 nếu tìm thấy, 0 nếu không có
 */
int tim_nguoi_choi(const char *ten, HoSoNguoiChoi *ket_qua);

/*
 * Xóa toàn bộ bảng xếp hạng.
 * Trả về: 1 nếu thành công, 0 nếu thất bại
 */
int xoa_bang_xep_hang(void);

#endif /* BANG_XEP_HANG_H */
