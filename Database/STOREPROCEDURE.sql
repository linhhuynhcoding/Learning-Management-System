use [LMS];

GO;

-- Thêm sinh viên vào trong Bảng SinhVien.
CREATE PROCEDURE spThemSV 
(
    @MSSV CHAR(20),   
    @TENSV NVARCHAR(100),
    @NAMSINH DATE,       
    @KHOA INT,           
    @MANGANH CHAR(10)    
)
AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION;
        
        IF EXISTS (SELECT 1 FROM SinhVien WHERE MSSV = @MSSV) 
        BEGIN
            THROW 50000, N'DA TON TAI THONG TIN SINH VIEN TRONG CSDL!', 1;
        END
		
        INSERT INTO SinhVien (MSSV, TENSV, NAMSINH, KHOA, MANGANH, TONGTINCHI, GPA)
        VALUES (@MSSV, @TENSV, @NAMSINH, @KHOA, @MANGANH, 0, 0);

        COMMIT TRANSACTION;
    END TRY

    BEGIN CATCH
        ROLLBACK TRANSACTION;
				SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
    END CATCH
END;

EXEC spThemSV @MSSV = '0512', @TENSV = N'HUỲNH VŨ NHẬT LINH', @NAMSINH = '04/30/2005', @KHOA = 2023, @MANGANH = 'MN0004';
DROP PROCEDURE spThemSV;

GO;

--Xóa sinh viên ra khỏi Bảng SinhVien.
CREATE PROCEDURE spXoaSV(@MSSV CHAR(20))
AS
BEGIN 
    BEGIN TRY
        BEGIN TRANSACTION;
        
        IF NOT EXISTS (SELECT 1 FROM SinhVien WHERE MSSV = @MSSV) 
        BEGIN
			PRINT N'KHONG TON TAI SINH VIEN TRONG CSDL!!';
            THROW 50000, N'KHONG TON TAI SINH VIEN TRONG CSDL!!', 1;
        END

        DELETE FROM SinhVien WHERE MSSV = @MSSV;

        COMMIT TRANSACTION;
    END TRY

    BEGIN CATCH
		PRINT N'ROLLBACK!';
        ROLLBACK TRANSACTION;
						SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
    END CATCH
END;

DROP PROCEDURE spXoaSv;

EXEC spXoaSV @MSSV = '051205008812';


--Sửa sinh viên trong Bảng SinhVien.
CREATE PROCEDURE spSuaSV(
	@MSSV CHAR(20),   
    @TENSV NVARCHAR(100),
    @NAMSINH DATE,       
    @KHOA INT,           
    @MANGANH CHAR(10)    
)
AS
BEGIN 
    BEGIN TRY
        BEGIN TRANSACTION;
        
        IF NOT EXISTS (SELECT 1 FROM SinhVien WHERE MSSV = @MSSV) 
        BEGIN
            THROW 50000, N'CHUA TON TAI THONG TIN SINH VIEN TRONG CSDL!', 1;
        END

		UPDATE SinhVien SET TENSV = @TENSV WHERE MSSV = @MSSV;
		UPDATE SinhVien SET NAMSINH = @NAMSINH WHERE MSSV = @MSSV;
		UPDATE SinhVien SET KHOA = @KHOA WHERE MSSV = @MSSV;
		UPDATE SinhVien SET MANGANH = @MANGANH WHERE MSSV = @MSSV;

        PRINT 'THÔNG TIN SINH VIÊN ĐÃ ĐƯỢC CẬP NHẬT THÀNH CÔNG!';
        COMMIT TRANSACTION;
    END TRY

    BEGIN CATCH
        ROLLBACK TRANSACTION;
								SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
    END CATCH
END 

EXEC spSuaSV @MSSV = '051205008812', @TENSV = N'HUYNH VU NHAT LINH 2', @NAMSINH = '09/30/2005', @KHOA = 2024, @MANGANH = 'MN0001';

DROP PROCEDURE spSuaSV;

--Thêm giảng viên vào trong Bảng GiangVien.
CREATE PROCEDURE spThemGV(
    @MSGV CHAR(20),
    @TENGV NVARCHAR(100),
    @NAMSINH DATE,
    @TRINHDO NVARCHAR(50)
)
AS
BEGIN
	BEGIN TRY
        BEGIN TRANSACTION;
		IF EXISTS (SELECT 1 FROM GiangVien WHERE MSGV = @MSGV)
		BEGIN
			THROW 50000, N'DA TON TAI THONG TIN GIANG VIEN TRONG CSDL!', 1;
		END

		INSERT INTO GiangVien (MSGV, TENGV, NAMSINH, TRINHDO)
		VALUES (@MSGV, @TENGV, @NAMSINH, @TRINHDO);

		COMMIT TRANSACTION;
		PRINT 'Giảng viên đã được thêm thành công!';
    END TRY

    BEGIN CATCH
        ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
    END CATCH
    
END;

EXEC spThemGV @MSGV = '13513158', @TENGV = N'HUỲNH VŨ NHẬT LINH', @NAMSINH = '04/30/2005', @TRINHDO = N'Tiến sĩ';
DROP PROCEDURE spThemGV;


--Xóa giảng viên ra khỏi Bảng GiangVien.
CREATE PROCEDURE spXoaGV(@MSGV CHAR(20))
AS
BEGIN 
    BEGIN TRY
        BEGIN TRANSACTION;
        
        IF NOT EXISTS (SELECT 1 FROM GiangVien WHERE MSGV = @MSGV) 
        BEGIN
			THROW 50000, N'KHONG TON TAI THONG TIN GIANG VIEN TRONG CSDL!', 1;

        END

        DELETE FROM GiangVien WHERE MSGV = @MSGV;

        PRINT 'GIẢNG VIÊN ĐÃ ĐƯỢC XÓA THÀNH CÔNG!';
        COMMIT TRANSACTION;
    END TRY

    BEGIN CATCH
        ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
    END CATCH
END;

EXEC spXoaGV @MSGV = '13513158';

DROP PROCEDURE spXoaGV;

--Sửa giảng viên trong Bảng GiangVien.
CREATE PROCEDURE spSuaGV(
    @MSGV CHAR(20),
    @TENGV NVARCHAR(100),
    @NAMSINH DATE,
    @TRINHDO NVARCHAR(50)
)
AS
BEGIN 
    BEGIN TRY
        BEGIN TRANSACTION;
        
        IF NOT EXISTS (SELECT 1 FROM GiangVien WHERE MSGV = @MSGV) 
        BEGIN
			THROW 50000, N'KHONG TON TAI THONG TIN GIANG VIEN TRONG CSDL!', 1;

        END

		UPDATE GiangVien SET TENGV = @TENGV WHERE MSGV = @MSGV;
		UPDATE GiangVien SET NAMSINH = @NAMSINH WHERE MSGV = @MSGV;
		UPDATE GiangVien SET TRINHDO = @TRINHDO WHERE MSGV = @MSGV;

        PRINT 'THÔNG TIN GIẢNG VIÊN ĐÃ ĐƯỢC CẬP NHẬT THÀNH CÔNG!';
        COMMIT TRANSACTION;
    END TRY

    BEGIN CATCH
        ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
    END CATCH
END 

EXEC spSuaGV @MSGV = '000001', @TENGV = N'HUỲNH VŨ NHẬT LINH 3', @NAMSINH = '08/30/2005', @TRINHDO = N'Phổ thông';
DROP PROCEDURE spSuaGV;

-- Mở một lớp mới.
CREATE PROCEDURE spThemLopHoc
(
	@MALH CHAR(10),
	@MAMH CHAR(10),
	@MAPG CHAR(10),
	@MSGV CHAR(20),
	@CA TINYINT,
	@NGAYHOC TINYINT,
	@NGAYSTART SMALLDATETIME
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION
		
		IF EXISTS (SELECT 1 FROM LopHoc WHERE MALH = @MALH) 
		BEGIN
			THROW 50000, N'DA TON TAI MA LOP HOC TRONG CSDL!', 1;
		END

		IF NOT EXISTS (SELECT 1 FROM MonHoc WHERE MAMH = @MAMH) 
		BEGIN
			THROW 50000, N'KHONG TON TAI MA MON HOC TRONG CSDL!', 1;
		END

		IF NOT EXISTS (SELECT 1 FROM GiangVien WHERE MSGV = @MSGV) 
        BEGIN
            THROW 50000, N'GIANG VIEN KHONG TON TAI TRONG CSDL!', 1;
        END

		IF NOT EXISTS (SELECT 1 FROM GV_MH WHERE MSGV = @MSGV AND MAMH = @MAMH) 
        BEGIN
            THROW 50000, N'KHONG CO QUAN HE GIUA GIANG VIEN VA MON HOC TRONG CSDL!', 1;
        END

		DECLARE @SOBUOI INT;
		DECLARE @NGAYEND SMALLDATETIME;
		SELECT @SOBUOI = SOBUOI FROM MonHoc WHERE MAMH = @MAMH;
		SET @NGAYEND = DATEADD(dd, @SOBUOI * 7, @NGAYSTART); -- MỘT TUẦN MỘT BUỔI

			
		DECLARE @CHECK1 TINYINT;
		EXEC spCheckGiohoc @MAPG = @MAPG, @CA = @CA, @NGAYHOC = @NGAYHOC, @NGAYSTART = @NGAYSTART, @NGAYEND = @NGAYEND, @CHECK = @CHECK1 OUTPUT;
		IF (@CHECK1 = 1)
		BEGIN
			PRINT N'PHÒNG HỌC VÀ GIỜ HỌC ĐÃ BỊ TRÙNG!';
			THROW 50000, N'PHONG HOC VA GIO HOC BI TRUNG!', 1;
		END
			
		EXEC spCheckGV @MSGV = @MSGV, @CA = @CA, @NGAYHOC = @NGAYHOC, @NGAYSTART = @NGAYSTART, @NGAYEND = @NGAYEND, @CHECK = @CHECK1 OUTPUT;
		IF (@CHECK1 = 1)
		BEGIN
			PRINT N'GIẢNG VIÊN ĐÃ BỊ TRÙNG LỊCH!';
			THROW 50000, N'GIANG VIEN BI TRUNG LICH!', 1;
		END
				
		INSERT INTO LopHoc (MALH, MAMH, MAPG, MSGV, CA, NGAYHOC, NGAYSTART, NGAYEND, TRANGTHAI)
		VALUES (@MALH, @MAMH, @MAPG, @MSGV, @CA, @NGAYHOC, @NGAYSTART, @NGAYEND, 0);

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		PRINT N'ROLLBACK!';
		ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END

INSERT INTO LopHoc (MALH, MAMH, MAPG, MSGV, CA, NGAYHOC, NGAYSTART, NGAYEND, TRANGTHAI)
VALUES ('LH00001', 'MH0001', 'P01', '000001', 1, 1, '1/1/2024', '3/11/2024', 0);
DELETE FROM LopHoc WHERE MALH = 'LH00001'
EXEC spThemLopHoc @MALH='LH00001', @MAMH= 'MH0001', @MAPG= 'P01', @MSGV= '000001', @CA=1, @NGAYHOC=1, @NGAYSTART='1/1/2024';

EXEC spThemLopHoc @MALH='LH00002', @MAMH= 'MH0001', @MAPG= 'P01', @MSGV= '000001', @CA=1, @NGAYHOC=1, @NGAYSTART='3/12/2024';

EXEC spThemLopHoc @MALH='LH00003', @MAMH= 'MH0001', @MAPG= 'P02', @MSGV= '000001', @CA=1, @NGAYHOC=1, @NGAYSTART='3/12/2024';


DROP PROCEDURE spThemLopHoc
-- Xóa lớp học chưa khóa.
CREATE PROCEDURE spXoaLopHoc
(
	@MALH CHAR(10)
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION

		IF NOT EXISTS (SELECT 1 FROM LopHoc WHERE MALH = @MALH) 
		BEGIN
			THROW 50000, N'KHONG TON TAI MA LOP HOC TRONG CSDL!', 1;
		END
		
		IF NOT EXISTS (SELECT 1 FROM LopHoc WHERE MALH = @MALH AND TRANGTHAI = 0) 
		BEGIN
			THROW 50000, N'LOP HOC DA KHOA!', 1;
		END

        DELETE FROM LopHoc WHERE MALH = @MALH;

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END

EXEC spXoaLopHoc @MALH='LH00001';
DROP PROCEDURE spXoaLopHoc

GO;

--Kiểm tra phòng học và giờ học này đã có lớp chưa
CREATE PROCEDURE spCheckGiohoc
(
	@MAPG CHAR(10),
	@CA TINYINT,
	@NGAYHOC TINYINT,
	@NGAYSTART SMALLDATETIME,
	@NGAYEND SMALLDATETIME,
	@CHECK TINYINT OUTPUT -- 0 là false, 1 là true
)
AS
BEGIN
	SET @CHECK = 0;
	IF EXISTS (
		SELECT 1 FROM LopHoc 
		WHERE MAPG = @MAPG AND CA = @CA AND NGAYHOC = @NGAYHOC AND (NGAYSTART <= @NGAYSTART AND NGAYEND >= @NGAYEND)
	) 
	BEGIN
		SET @CHECK = 1;
	END
END

GO;

DECLARE @CHECK1 TINYINT;
EXEC spCheckGiohoc @MAPG = 'P01', @CA = 1, @NGAYHOC = 1, @NGAYSTART = '1/1/2024', @NGAYEND = '2/11/2024', @CHECK = @CHECK1 OUTPUT;
PRINT @CHECK1;
DROP PROCEDURE spCheckGiohoc

--Kiểm tra giảng viên và giờ học này đã có lớp chưa
CREATE PROCEDURE spCheckGV
(
	@MSGV CHAR(20),
	@CA TINYINT,
	@NGAYHOC TINYINT,
	@NGAYSTART SMALLDATETIME,
	@NGAYEND SMALLDATETIME,
	@CHECK TINYINT OUTPUT -- 0 là false, 1 là true
)
AS
BEGIN
	SET @CHECK = 0;
	IF EXISTS (
		SELECT 1 FROM LopHoc 
		WHERE MSGV = @MSGV AND CA = @CA AND NGAYHOC = @NGAYHOC AND (NGAYSTART <= @NGAYSTART AND NGAYEND >= @NGAYEND)
	) 
	BEGIN
		SET @CHECK = 1;
	END
END
DROP PROCEDURE spCheckGV

GO;

DECLARE @CHECK1 TINYINT;
EXEC spCheckGV @MSGV = '000001', @CA = 1, @NGAYHOC = 1, @NGAYSTART = '1/1/2024', @NGAYEND = '2/11/2024', @CHECK = @CHECK1 OUTPUT;
PRINT @CHECK1;
DROP PROCEDURE spCheckGV

-- Tạo tài khoản ADMIN
CREATE PROCEDURE spTaoTK
(
	@ID VARCHAR(40),
	@USERNAME VARCHAR(50),
	@PASSWORD VARCHAR(255)
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION

		IF EXISTS (SELECT 1 FROM TaiKhoan WHERE USERNAME = @USERNAME) 
		BEGIN
			THROW 50000, 'DA TON TAI USERNAME TRONG CSDL!', 1;
		END

		INSERT INTO TaiKhoan (ID, USERNAME, PASSWORD, ROLE)
		VALUES (@ID, @USERNAME, @PASSWORD, 0);

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
				SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END

drop procedure spTaoTK
GO;

-- Giảng viên thêm môn
CREATE PROCEDURE spGVthemMon
(
	@MSGV CHAR(20),
	@MAMH CHAR(10)
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION
		
		IF NOT EXISTS (SELECT 1 FROM MonHoc WHERE MAMH = @MAMH) 
		BEGIN
			THROW 50000, N'KHONG TON TAI MA MON HOC TRONG CSDL!', 1;
		END

		IF EXISTS (SELECT 1 FROM GV_MH WHERE MAMH = @MAMH AND MSGV = @MSGV) 
		BEGIN
			THROW 50000, N'DA CO QUAN HE GIUA GIANG VIEN VA MON HOC TRONG CSDL!', 1;
		END

		INSERT INTO GV_MH (MSGV, MAMH)
		VALUES (@MSGV, @MAMH);

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		PRINT N'ROLLBACK!';
		ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END
GO;

EXEC spGVthemMon @MSGV='000001', @MAMH='MH0001';
drop procedure spGVthemMon
-- Giảng viên xóa môn
CREATE PROCEDURE spGVxoaMon
(
	@MSGV CHAR(20),
	@MAMH CHAR(10)
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION
		
		IF NOT EXISTS (SELECT 1 FROM MonHoc WHERE MAMH = @MAMH) 
		BEGIN
			THROW 50000, N'KHONG TON TAI MA MON HOC TRONG CSDL!', 1;
		END

		IF NOT EXISTS (SELECT 1 FROM GV_MH WHERE MAMH = @MAMH AND MSGV = @MSGV) 
		BEGIN
			THROW 50000, N'KHONG TON TAI MA MON HOC TRONG CSDL!', 1;
		END

		DELETE FROM GV_MH WHERE MAMH = @MAMH AND MSGV = @MSGV;

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END
EXEC spGVxoaMon @MSGV='000001', @MAMH='MH0001';

DROP PROCEDURE spGVxoaMon;
GO;

-- Xuất danh sách lớp theo mã Lớp học
CREATE PROCEDURE spXuatDSLtheoMALH
(
	@MALH CHAR(10)
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION
		
		IF NOT EXISTS (SELECT 1 FROM LopHoc WHERE MALH = @MALH) 
		BEGIN
			THROW 50000, N'KKHONG TON TAI MA LOP HOC TRONG CSDL!', 1;
		END

		SELECT * FROM DSLOP AS T1
		JOIN SinhVien AS T2 ON T1.MSSV = T2.MSSV AND T1.MALH = @MALH;
		--WHERE MALH = @MALH ;

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
	END CATCH;
END
EXEC spXuatDSLtheoMALH @MALH='LH00002';
DROP PROCEDURE spXuatDSLtheoMALH;

GO;

-- Cập nhật điểm số theo mã Lớp, mssv
CREATE PROCEDURE spCapnhatdiemso
(
	@MALH CHAR(10), 
	@MSSV CHAR(20), 
	@GKY FLOAT, 
	@CKY FLOAT
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION
	
		DECLARE @MAMH CHAR(10); 

		IF NOT EXISTS (
			SELECT 1 FROM DSLOP WHERE MSSV = @MSSV AND MALH = @MALH
		)
		BEGIN
			THROW 50000, N'KHONG TON TAI QUAN HE GIUA MA LOP HOC VA MSSV TRONG CSDL!', 1;
		END
		
		SELECT @MAMH = MAMH FROM LopHoc WHERE MALH = @MALH;

		IF NOT EXISTS (
			SELECT 1 FROM DiemSo WHERE MAMH = @MAMH AND MSSV = @MSSV
		)
		BEGIN 
			INSERT INTO DiemSo (MSSV, MAMH, D_GKY, D_CKY, TONG, TRANGTHAI) VALUES (@MSSV, @MAMH, 0, 0, 0, 0);
		END
		
		UPDATE DiemSo SET D_GKY = @GKY WHERE MAMH = @MAMH AND MSSV = @MSSV;
		UPDATE DiemSo SET D_CKY = @CKY WHERE MAMH = @MAMH AND MSSV = @MSSV;
		UPDATE DiemSo SET TONG = (@GKY + @CKY)/2 WHERE MAMH = @MAMH AND MSSV = @MSSV;

		DECLARE @TONG TINYINT;
		SELECT @TONG = TONG FROM DiemSo WHERE MAMH = @MAMH AND MSSV = @MSSV;
		
		IF (@TONG >= 5) 
		BEGIN
			UPDATE DiemSo SET TRANGTHAI = 1 WHERE MAMH = @MAMH AND MSSV = @MSSV;
		END
		ELSE 
		BEGIN 
			UPDATE DiemSo SET TRANGTHAI = 0 WHERE MAMH = @MAMH AND MSSV = @MSSV;
		END
		
		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END
GO;

EXEC spCapnhatdiemso @MALH='LH00001', @MSSV='051205008812', @GKY=10, @CKY=7;

drop procedure spCapnhatdiemso;
-- Đổi password
CREATE PROCEDURE spDoiMK
(
	@USERNAME VARCHAR(50),
	@MKMOI VARCHAR(255)
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION
		
		IF NOT EXISTS (SELECT 1 FROM TaiKhoan WHERE USERNAME = @USERNAME) 
		BEGIN
			THROW 50000, N'KHONG TON TAI USERNAME TRONG CSDL!', 1;
		END

		UPDATE TaiKhoan SET PASSWORD = @MKMOI WHERE USERNAME = @USERNAME;

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
	END CATCH;
END
drop procedure spDoiMK;

GO;

-- Đăng ký lớp
CREATE PROCEDURE spDangkyLop
(
	@MSSV CHAR(20),
	@MALH CHAR(10)

)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION
		
		IF NOT EXISTS (SELECT 1 FROM LopHoc WHERE MALH = @MALH AND TRANGTHAI = 0) 
		BEGIN
			THROW 50000, N'LOP HOC DA KHOA HOAC KHONG TON TAI!', 1;
		END

		DECLARE @CHECK1 TINYINT,
		@CA TINYINT,
		@NGAYHOC TINYINT,
		@NGAYSTART SMALLDATETIME,
		@NGAYEND SMALLDATETIME;

		SELECT @CA = CA, @NGAYHOC = NGAYHOC, @NGAYSTART = NGAYSTART, @NGAYEND = NGAYEND
		FROM LopHoc
		WHERE MALH = @MALH;
		
		EXEC spCheckLichTrung @MSSV = @MSSV, @CA = @CA, @NGAYHOC = @NGAYHOC, @NGAYSTART = @NGAYSTART, @NGAYEND = @NGAYEND, @CHECK = @CHECK1 OUTPUT;
		IF (@CHECK1 = 1)
		BEGIN
			THROW 50000, N'SINH VIEN DA BI TRUNG LICH!', 1;
		END
 
		INSERT INTO DSLOP (MALH, MSSV)
		VALUES (@MALH, @MSSV);

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END
go;

EXEC spDangkyLop @MSSV='051205008812', @MALH='LH00001';
drop procedure spDangkyLop;
--Kiểm tra Sinh viên và giờ học này đã có lớp chưa
CREATE PROCEDURE spCheckLichTrung
(
	@MSSV CHAR(20),
	@CA TINYINT,
	@NGAYHOC TINYINT,
	@NGAYSTART SMALLDATETIME,
	@NGAYEND SMALLDATETIME,
	@CHECK TINYINT OUTPUT -- 0 là false, 1 là true
)
AS
BEGIN
	SET @CHECK = 0;
	IF EXISTS (
		--SELECT T1.MALH, T2.CA, T2.NGAYHOC, T2.NGAYSTART, T2.NGAYEND
		SELECT 1
		FROM 
			(SELECT MALH FROM DSLOP WHERE MSSV = @MSSV) AS T1
			JOIN LopHoc AS T2 ON T1.MALH = T2.MALH
		WHERE CA = @CA AND NGAYHOC = @NGAYHOC AND @NGAYSTART >= NGAYSTART AND @NGAYEND <= @NGAYEND
	) 
	BEGIN
		SET @CHECK = 1;
	END
END

go;

--Lấy sỉ số hiện tại của lớp 
CREATE PROCEDURE spLaySiso
(
	@MALH CHAR(10),
	@num INT OUTPUT
)
AS
BEGIN
	SELECT @num = COUNT(*) FROM DSLOP WHERE MALH = @MALH;
END
go;

DECLARE @SISO INT;
EXEC spLaySiso @MALH='LH00001', @num = @SISO OUTPUT;
PRINT @SISO;

-- Hủy lớp
CREATE PROCEDURE spHuyLop
(
	@MSSV CHAR(20),
	@MALH CHAR(10)

)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION
		
		IF NOT EXISTS (SELECT 1 FROM LopHoc WHERE MALH = @MALH) 
		BEGIN
			THROW 50000, N'KHONG TON TAI MA LOP HOC TRONG CSDL!', 1;
		END
		
		IF NOT EXISTS (SELECT 1 FROM LopHoc WHERE MALH = @MALH AND TRANGTHAI = 0) 
		BEGIN
			THROW 50000, N'LOP HOC DA KHOA!', 1;
		END

		DELETE FROM DSLOP WHERE MALH = @MALH AND MSSV = @MSSV;

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END
go;
drop procedure spHuyLop;

EXEC spHuyLop @MSSV='051205008812', @MALH='LH00001';
--Hiển thị môn học, điểm, trạng thái

CREATE PROCEDURE spKetquahoctap
(
	@MSSV CHAR(20)
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION

		SELECT *
		FROM (
			SELECT MAMH, T1.MALH
			FROM 
				(SELECT MALH FROM DSLOP WHERE MSSV = @MSSV) AS T1
				JOIN LopHoc AS T2 ON T1.MALH = T2.MALH
		) AS T3
		JOIN DiemSo AS T4 ON T4.MSSV = @MSSV AND T4.MAMH = T3.MAMH

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END
go;

EXEC spKetquahoctap @MSSV='051205008812';
drop procedure spKetquahoctap

go;

--Login
CREATE PROCEDURE spLogin
(
	@USERNAME VARCHAR(50),
	@PASSWORD VARCHAR(255),
	@ROLE TINYINT
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION

		IF (NOT EXISTS (SELECT 1 FROM TaiKhoan WHERE USERNAME =@USERNAME))
		BEGIN 
			THROW 50000, 'KHONG TON TAI TAI KHOAN!', 1;
		END

		IF (@ROLE=2 AND NOT EXISTS (SELECT 1 FROM TK_SV WHERE ID =@USERNAME))
		BEGIN 
			THROW 50000, 'KHONG TON TAI TAI KHOAN!', 1;
		END
		
		IF (@ROLE=1 AND NOT EXISTS (SELECT 1 FROM TK_GV WHERE ID =@USERNAME))
		BEGIN 
			THROW 50000, 'KHONG TON TAI TAI KHOAN!', 1;
		END

		IF (NOT EXISTS (SELECT 1 FROM TaiKhoan WHERE USERNAME =@USERNAME AND PASSWORD = @PASSWORD))
		BEGIN 
			THROW 50000, 'SAI MAT KHAU!', 1;
		END
		
		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END
go;

EXEC spLogin @USERNAME='051205008812', @PASSWORD='20050430', @ROLE=2;
drop procedure spLogin


-- khóa lớp
CREATE PROCEDURE spKhoaLop
(
	@MALH CHAR(10)
)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION
		
		IF NOT EXISTS (SELECT 1 FROM LopHoc WHERE MALH = @MALH) 
		BEGIN
			THROW 50000, N'KHONG TON TAI MA LOP HOC TRONG CSDL!', 1;
		END
		
		IF NOT EXISTS (SELECT 1 FROM LopHoc WHERE MALH = @MALH AND TRANGTHAI = 0) 
		BEGIN
			THROW 50000, N'LOP HOC DA KHOA!', 1;
		END

		UPDATE LopHoc SET TRANGTHAI = 1 WHERE MALH = @MALH;

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
        ERROR_NUMBER() AS ErrorNumber,        -- Mã lỗi
        ERROR_MESSAGE() AS ErrorMessage,     -- Thông báo lỗi
        ERROR_SEVERITY() AS ErrorSeverity,   -- Mức độ nghiêm trọng
        ERROR_STATE() AS ErrorState,         -- Trạng thái lỗi
        ERROR_LINE() AS ErrorLine,           -- Dòng xảy ra lỗi
        ERROR_PROCEDURE() AS ErrorProcedure; -- Tên thủ tục xảy ra lỗi (nếu có)
	END CATCH;
END
go;
drop procedure spKhoaLop;