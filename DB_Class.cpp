//---------------------------------------------------------------------------

#pragma hdrstop

#include "DB_Class.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*class DataWriter {
public:
	sqlite3* db;
	DataWriter() {
		int con_db = sqlite3_open("BAZA", &db);
		sqlite3_stmt* pStatement;
		const char* sql = "CREATE TABLE IF NOT EXIST clusters (id int NOT NULL AUTOINCREMENT, number int64, signature TEXT, disk TEXT)";
		sqlite3_exec(db, sql, NULL, NULL, NULL);
	};

	void insertData(ULONGLONG cluster_number, const wchar_t* signature, const wchar_t* L) {
		sqlite3_stmt* pStatement;

		const char* sql = "INSERT INTO clusters VALUES (?, ?, ?)";

		int execResult = sqlite3_prepare_v2(
			db,
			sql,
			-1,
			&pStatement,
			NULL
		);

		sqlite3_bind_int64(pStatement, 1, cluster_number);
		sqlite3_bind_text16(pStatement, 2, signature, -1, SQLITE_TRANSIENT);
		sqlite3_bind_text16(pStatement, 3, L, -1, SQLITE_TRANSIENT);
		sqlite3_step(pStatement);
		sqlite3_finalize(pStatement);

	}

	void selectData() {
		sqlite3_stmt* pStatement;

		const char* sql = "SELECT * FROM clusters";
		int execResult = sqlite3_prepare_v2(
			db,
			sql,
			-1,
			&pStatement,
			NULL
		);

		int execResultStep = sqlite3_step(pStatement);
		int id = sqlite3_column_int(pStatement, 0);
		ULONGLONG cluster_number = sqlite3_column_int64(pStatement, 1);
		const void* signature = sqlite3_column_text16(pStatement, 2);
		const void* L = sqlite3_column_text16(pStatement, 3);
		sqlite3_free((void *)signature);
		sqlite3_free((void *)L);
		sqlite3_finalize(pStatement);


	}

	void closeConnection() {
		sqlite3_close(db);
	}

	~DataWriter() {
		delete db;
	}
}; */