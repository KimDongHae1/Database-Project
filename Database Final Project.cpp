#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#include <iostream>
#include <string>

using namespace std;

void finish_with_error(MYSQL *conn)
{
	//MySQL의 에러 원인을 문자열로 반환
	fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
	exit(1);
}

void print_main_menu()
{
	// Main Menu
	printf("\t+----------MAIN--------+\n");
	printf("\t|%-21s|\n", "1. Beer Recommendation");
	printf("\t|----------------------|\n");
	printf("\t|%-21s|\n", "2. Food Recommendation");
	printf("\t|----------------------|\n");
	printf("\t|%-21s |\n", "3. Beer Ranking");
	printf("\t|----------------------|\n");
	printf("\t|%-21s |\n", "4. Beer Info");
	printf("\t|----------------------|\n");
	printf("\t|%-21s |\n", "5. Slae Info");
	printf("\t|----------------------|\n");
	printf("\t|%-21s |\n", "6. Admin");
	printf("\t+----------------------+\n\n");
}

string productName = "";
string productGroup = "";
string beerType = "";
int alcohol = 0;
string country = "";
string taste = "";
string flavor = "";
string feeling = "";
string storeName = "";
string foodName = "";
string oldName = "";
string newName = "";

int input = 0;

int not_select_or_previous_menu(string input)
{
	if (strcmp(input.c_str(), "0") == 0) return 0;

	if (strcmp(input.c_str(), "1") == 0) return 1;

	return 2;
}

int not_select_or_previous_menu(int input)
{
	if (input == 0) return 0;

	if (input == 1) return 1;

	return 2;
}

int main(int argc, char* agrv[])
{
	// init SQL
	//연결함수, MySQL변수 초기화
	MYSQL *conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	//(MySQL전용변수, 서버ip, 유저이름, 유저 비밀번호, DB, 포트, 소켓, flag)
	if (mysql_real_connect(conn, "localhost", "root", "q1234567", "testdb", 0, NULL, CLIENT_MULTI_QUERIES) == NULL)
	{
		finish_with_error(conn);
	}

	MYSQL_RES *result;
	int num_fields;
	MYSQL_ROW row;
	MYSQL_FIELD *field;

	int num_rows;
	int nr;

	char buf[1024];

	printf("\n");
	print_main_menu();
	int menu_num;
	while (1)
	{
		printf("\nSYSTEM : ");
		printf("SELECT MENU (0 to exit) : ");
		cin >> menu_num;

		switch (menu_num)
		{
		// exit
		case 0:
			return 0;

		// Beer Recommendatio
		case 1:
			// 항목들을 골라 추천받기

			// 종류 안내
			if (mysql_query(conn, "SELECT distinct beerType FROM beerInfo"))
			{
				finish_with_error(conn);
			}

			result = mysql_store_result(conn);
			if (result == NULL)
			{
				finish_with_error(conn);
			}

			num_fields = mysql_num_fields(result);
			
			num_rows = mysql_num_rows(result);
			nr = 0;

			printf("\nSYSTEM : \n\n");
			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			printf("\n");

			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (i == 0)
					{
						int p = 0;
						while (field = mysql_fetch_field(result))
						{
							printf("\t|%20s", field->name);
							if(p == num_fields-1){
								printf("|\n");
								for(int m = 0 ; m < num_fields ; m++){
									printf("\t=====================");
								}
								printf("\n");
							}
							p++;
						}
					}
					printf("\t|%20s", row[i] ? row[i] : "NULL");
				}
				printf("|\n");
				nr++;
			}

			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }

			printf("\n");
			mysql_free_result(result);

			// 종류 선택
			printf("\nSYSTEM : ");
			printf("(not select : 1, previous menu : 0)\n 맥주 종류를 입력하세요 : ");
			cin.ignore();
			getline(cin, beerType, '\n');
			input = not_select_or_previous_menu(beerType);
			if (input == 0) break;
			if (input == 1) beerType = "";


			//도수 안내
			if (mysql_query(conn, "SELECT distinct alcohol beerType FROM beerInfo ORDER BY alcohol asc"))
			{
				finish_with_error(conn);
			}

			result = mysql_store_result(conn);

			if (result == NULL)
			{
				finish_with_error(conn);
			}

			num_fields = mysql_num_fields(result);

			num_rows = mysql_num_rows(result);
			nr = 0;

			printf("\nSYSTEM : \n\n");
			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			printf("\n");

			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (i == 0)
					{
						int p = 0;
						while (field = mysql_fetch_field(result))
						{
							printf("\t|%20s", field->name);
							if(p == num_fields-1){
								printf("|\n");
								for(int m = 0 ; m < num_fields ; m++){
									printf("\t=====================");
								}
								printf("\n");
							}
							p++;
						}
					}
					printf("\t|%20s", row[i] ? row[i] : "NULL");
				}
				printf("|\n");
				nr++;
			}

			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }

			printf("\n");
			mysql_free_result(result);

			//도수 선택
			printf("\nSYSTEM : ");
			printf("(not select : 1, previous menu : 0)\n 맥주 도수 입력하세요 : ");
			cin >> alcohol;
			input = not_select_or_previous_menu(alcohol);
			if (input == 0) break;
			if (input == 1) alcohol = 0;


			// 국가 안내
			if (mysql_query(conn, "SELECT distinct country FROM beercountry"))
			{
				finish_with_error(conn);
			}

			result = mysql_store_result(conn);
			if (result == NULL)
			{
				finish_with_error(conn);
			}

			num_fields = mysql_num_fields(result);

			num_rows = mysql_num_rows(result);
			nr = 0;

			printf("\nSYSTEM : \n\n");
			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			printf("\n");

			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (i == 0)
					{
						int p = 0;
						while (field = mysql_fetch_field(result))
						{
							printf("\t|%20s", field->name);
							if(p == num_fields-1){
								printf("|\n");
								for(int m = 0 ; m < num_fields ; m++){
									printf("\t=====================");
								}
								printf("\n");
							}
							p++;
						}
					}
					printf("\t|%20s", row[i] ? row[i] : "NULL");
				}
				printf("|\n");
				nr++;
			}

			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }

			printf("\n");
			mysql_free_result(result);

			// 국가 선택
			printf("\nSYSTEM : ");
			printf("(not select : 1, previous menu : 0)\n 맥주 생산국을 입력하세요 : ");
			cin >> country;
			input = not_select_or_previous_menu(country);
			if (input == 0) break;
			if (input == 1) country = "";


			// 맛 안내
			if (mysql_query(conn, "SELECT distinct taste1 FROM beerTaste"))
			{
				finish_with_error(conn);
			}

			result = mysql_store_result(conn);
			if (result == NULL)
			{
				finish_with_error(conn);
			}

			num_fields = mysql_num_fields(result);
			
			num_rows = mysql_num_rows(result);
			nr = 0;

			printf("\nSYSTEM : \n\n");
			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			printf("\n");

			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (i == 0)
					{
						int p = 0;
						while (field = mysql_fetch_field(result))
						{
							printf("\t|%20s", field->name);
							if(p == num_fields-1){
								printf("|\n");
								for(int m = 0 ; m < num_fields ; m++){
									printf("\t=====================");
								}
								printf("\n");
							}
							p++;
						}
					}
					printf("\t|%20s", row[i] ? row[i] : "NULL");
				}
				printf("|\n");
				nr++;
			}

			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			
			printf("\n");
			mysql_free_result(result);

			// 맛 선택
			printf("\nSYSTEM : ");
			printf("(not select : 1, previous menu : 0)\n 맥주 맛을 입력하세요 : ");
			cin >> taste;
			input = not_select_or_previous_menu(taste);
			if (input == 0) break;
			if (input == 1) taste = "";


			// 향 안내
			if (mysql_query(conn, "SELECT distinct flavor1 FROM beerflavor"))
			{
				finish_with_error(conn);
			}

			result = mysql_store_result(conn);
			if (result == NULL)
			{
				finish_with_error(conn);
			}

			num_fields = mysql_num_fields(result);

			num_rows = mysql_num_rows(result);
			nr = 0;

			printf("\nSYSTEM : \n\n");
			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			printf("\n");

			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (i == 0)
					{
						int p = 0;
						while (field = mysql_fetch_field(result))
						{
							printf("\t|%20s", field->name);
							if(p == num_fields-1){
								printf("|\n");
								for(int m = 0 ; m < num_fields ; m++){
									printf("\t=====================");
								}
								printf("\n");
							}
							p++;
						}
					}
					printf("\t|%20s", row[i] ? row[i] : "NULL");
				}
				printf("|\n");
				nr++;
			}

			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
						
			printf("\n");
			mysql_free_result(result);

			// 향 선택
			printf("\nSYSTEM : ");
			printf("(not select : 1, previous menu : 0)\n 맥주 향을 입력하세요 : ");
			cin >> flavor;
			input = not_select_or_previous_menu(flavor);
			if (input == 0) break;
			if (input == 1) flavor = "";


			// 목넘김 선택
			if (mysql_query(conn, "SELECT distinct feeling FROM beerfeeling"))
			{
				finish_with_error(conn);
			}

			result = mysql_store_result(conn);
			if (result == NULL)
			{
				finish_with_error(conn);
			}

			num_fields = mysql_num_fields(result);

			num_rows = mysql_num_rows(result);
			nr = 0;

			printf("\nSYSTEM : \n\n");
			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			printf("\n");

			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (i == 0)
					{
						int p = 0;
						while (field = mysql_fetch_field(result))
						{
							printf("\t|%20s", field->name);
							if(p == num_fields-1){
								printf("|\n");
								for(int m = 0 ; m < num_fields ; m++){
									printf("\t=====================");
								}
								printf("\n");
							}
							p++;
						}
					}
					printf("\t|%20s", row[i] ? row[i] : "NULL");
				}
				printf("|\n");
				nr++;
			}

			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			
			printf("\n");
			mysql_free_result(result);

			// 목넘김 선택
			printf("\nSYSTEM : ");
			printf("(not select : 1, previous menu : 0)\n 맥주 목넘김 입력하세요 : ");
			cin >> feeling;
			input = not_select_or_previous_menu(feeling);
			if (input == 0) break;
			if (input == 1) feeling = "";



			printf("\nSYSTEM : ");
			cout << "항목" << "type - alcohol - country - taste - flavor - feeling - store\n"
				<< "선택" << beerType << " - " << alcohol << " - " << country << " - " << taste << " - " << flavor << " - "
				<< feeling << " - " << storeName << "\n";


			// 추천 view 생성

			//전체를 선택하는 view
			//sprintf_s(buf, "CREATE VIEW recommend1 AS SELECT * FROM beerinfo NATURAL JOIN beercountry NATURAL JOIN beertaste NATURAL JOIN beerflavor NATURAL JOIN beerfeeling NATURAL JOIN storecatalog");
			
			sprintf_s(buf, "CREATE VIEW recommend1 AS SELECT * FROM beerinfo NATURAL JOIN beercountry NATURAL JOIN beertaste NATURAL JOIN beerflavor NATURAL JOIN beerfeeling NATURAL JOIN storecatalog WHERE (beerType = '%s') and (alcohol = '%d') and (country = '%s') and (taste1 = '%s') and (flavor1 = '%s')", beerType, alcohol, country, taste, flavor);
			if (mysql_query(conn, buf))
			{
				finish_with_error(conn);
			}

			// 추천 view 확인
			if (mysql_query(conn, "SELECT productName FROM recommend1"))
			{
				finish_with_error(conn);
			}

			result = mysql_store_result(conn);
			if (result == NULL)
			{
				finish_with_error(conn);
			}

			num_fields = mysql_num_fields(result);

			num_rows = mysql_num_rows(result);
			nr = 0;

			printf("\nSYSTEM : \n\n");
			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			printf("\n");

			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (i == 0)
					{
						int p = 0;
						while (field = mysql_fetch_field(result))
						{
							printf("\t|%20s", field->name);
							if(p == num_fields-1){
								printf("|\n");
								for(int m = 0 ; m < num_fields ; m++){
									printf("\t=====================");
								}
								printf("\n");
							}
							p++;
						}
					}
					printf("\t|%20s", row[i] ? row[i] : "NULL");
				}
				printf("|\n");
				nr++;
			}

			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			
			printf("\n");
			mysql_free_result(result);
			break;


		// Food Recommendation
		case 2:
			printf("\nSYSTEM : ");
			printf("\n1. 안주먼저\n");
			printf("2. 맥주먼저\n");
			printf("3. 맥주종류먼저\n");
			printf("메뉴를 선택하세요 : ");
			cin >> input;

			//2-1. 안주먼저
			if (input == 1)
			{
				// Query
				if (mysql_query(conn, "SELECT distinct foodName FROM food"))
				{
					finish_with_error(conn);
				}

				// Print Query Result
				result = mysql_store_result(conn);
				if (result == NULL)
				{
					finish_with_error(conn);
				}

				num_fields = mysql_num_fields(result);

				num_rows = mysql_num_rows(result);
				nr = 0;

				printf("\nSYSTEM : \n\n");
				for(int m = 0 ; m < num_fields ; m++){
			        if(m==0)
			            printf("\t+------------------------");
			        else if( m == num_fields-1)
			            printf("-------------------------+");
			        else
			            printf("------------------------");
			    }
				printf("\n");

				while (row = mysql_fetch_row(result))
				{
					for (int i = 0; i < num_fields; i++)
					{
						if (i == 0)
						{
							int p = 0;
							while (field = mysql_fetch_field(result))
							{
								printf("\t|%20s", field->name);
								if(p == num_fields-1){
									printf("|\n");
									for(int m = 0 ; m < num_fields ; m++){
										printf("\t=====================");
									}
									printf("\n");
								}
								p++;
							}
						}
						printf("\t|%20s", row[i] ? row[i] : "NULL");
					}
					printf("|\n");
					nr++;
				}

				for(int m = 0 ; m < num_fields ; m++){
			        if(m==0)
			            printf("\t+------------------------");
			        else if( m == num_fields-1)
			            printf("-------------------------+");
			        else
			            printf("------------------------");
			    }
				
				printf("\n");
				mysql_free_result(result);

				// 안주 선택
				printf("\nSYSTEM : ");
				printf("(not select : 1, previous menu : 0)\n 음식 이름을 입력하세요 : ");
				cin.ignore();
				getline(cin, foodName, '\n');
				input = not_select_or_previous_menu(foodName);
				if (input == 0) break;
				if (input == 1) storeName = "";

				// Query
				sprintf_s(buf, "SELECT beerinfo.productName, beerinfo.beertype FROM food, beerinfo WHERE food.beertype = beerinfo.beertype and foodName = '%s'", foodName);

				if (mysql_query(conn, buf))
				{
					finish_with_error(conn);
				}

				result = mysql_store_result(conn);
				if (result == NULL)
				{
					finish_with_error(conn);
				}

				num_fields = mysql_num_fields(result);

				num_rows = mysql_num_rows(result);
				nr = 0;

				printf("\nSYSTEM : \n\n");
				for(int m = 0 ; m < num_fields ; m++){
			        if(m==0)
			            printf("\t+------------------------");
			        else if( m == num_fields-1)
			            printf("-------------------------+");
			        else
			            printf("------------------------");
			    }
				printf("\n");

				while (row = mysql_fetch_row(result))
				{
					for (int i = 0; i < num_fields; i++)
					{
						if (i == 0)
						{
							int p = 0;
							while (field = mysql_fetch_field(result))
							{
								printf("\t|%20s", field->name);
								if(p == num_fields-1){
									printf("|\n");
									for(int m = 0 ; m < num_fields ; m++){
										printf("\t=====================");
									}
									printf("\n");
								}
								p++;
							}
						}
						printf("\t|%20s", row[i] ? row[i] : "NULL");
					}
					printf("|\n");
					nr++;
				}

				for(int m = 0 ; m < num_fields ; m++){
			        if(m==0)
			            printf("\t+------------------------");
			        else if( m == num_fields-1)
			            printf("-------------------------+");
			        else
			            printf("------------------------");
			    }
				
				printf("\n");
				mysql_free_result(result);
			}


			//2-2. 맥주먼저
			if (input == 2)
			{
				// Query
				if (mysql_query(conn, "SELECT distinct productName FROM beernfo"))
				{
					finish_with_error(conn);
				}

				// Print Query Result
				result = mysql_store_result(conn);
				if (result == NULL)
				{
					finish_with_error(conn);
				}

				num_fields = mysql_num_fields(result);

				num_rows = mysql_num_rows(result);
				nr = 0;

				printf("\nSYSTEM : \n\n");
				for(int m = 0 ; m < num_fields ; m++){
			        if(m==0)
			            printf("\t+------------------------");
			        else if( m == num_fields-1)
			            printf("-------------------------+");
			        else
			            printf("------------------------");
			    }
				printf("\n");

				while (row = mysql_fetch_row(result))
				{
					for (int i = 0; i < num_fields; i++)
					{
						if (i == 0)
						{
							int p = 0;
							while (field = mysql_fetch_field(result))
							{
								printf("\t|%20s", field->name);
								if(p == num_fields-1){
									printf("|\n");
									for(int m = 0 ; m < num_fields ; m++){
										printf("\t=====================");
									}
									printf("\n");
								}
								p++;
							}
						}
						printf("\t|%20s", row[i] ? row[i] : "NULL");
					}
					printf("|\n");
					nr++;
				}

				for(int m = 0 ; m < num_fields ; m++){
			        if(m==0)
			            printf("\t+------------------------");
			        else if( m == num_fields-1)
			            printf("-------------------------+");
			        else
			            printf("------------------------");
			    }
				
				printf("\n");
				mysql_free_result(result);

				// 맥주 선택
				printf("\nSYSTEM : ");
				printf("(not select : 1, previous menu : 0)\n 맥주 이름을 입력하세요 : ");
				cin.ignore();
				getline(cin, productName, '\n');
				input = not_select_or_previous_menu(productName);
				if (input == 0) break;
				if (input == 1) storeName = "";

				// Query
				sprintf_s(buf, "SELECT foodName FROM food, beerinfo WHERE food.beertype = beerinfo.beertype and productName = '%s'", productName);

				if (mysql_query(conn, buf))
				{
					finish_with_error(conn);
				}

				result = mysql_store_result(conn);
				if (result == NULL)
				{
					finish_with_error(conn);
				}

				num_fields = mysql_num_fields(result);

				num_rows = mysql_num_rows(result);
				nr = 0;

				printf("\nSYSTEM : \n\n");
				for(int m = 0 ; m < num_fields ; m++){
			        if(m==0)
			            printf("\t+------------------------");
			        else if( m == num_fields-1)
			            printf("-------------------------+");
			        else
			            printf("------------------------");
			    }
				printf("\n");

				while (row = mysql_fetch_row(result))
				{
					for (int i = 0; i < num_fields; i++)
					{
						if (i == 0)
						{
							int p = 0;
							while (field = mysql_fetch_field(result))
							{
								printf("\t|%20s", field->name);
								if(p == num_fields-1){
									printf("|\n");
									for(int m = 0 ; m < num_fields ; m++){
										printf("\t=====================");
									}
									printf("\n");
								}
								p++;
							}
						}
						printf("\t|%20s", row[i] ? row[i] : "NULL");
					}
					printf("|\n");
					nr++;
				}

				for(int m = 0 ; m < num_fields ; m++){
			        if(m==0)
			            printf("\t+------------------------");
			        else if( m == num_fields-1)
			            printf("-------------------------+");
			        else
			            printf("------------------------");
			    }

				printf("\n");
				mysql_free_result(result);
			}
			break;


		// Beer Ranking
		case 3:
			printf("\nSYSTEM : 2018 맥주순위를 알려줍니다.\n");
			printf("\nSYSTEM : 'yearPoint' 는 검색량과 판매량을 종합한 점수입니다.\n");

			// Query
			if (mysql_query(conn, "SELECT productName, SalePoint.year, (yearSale + yearSearch) as yearPoint FROM (SELECT productName, year, sum(11-ranking)*10 as yearSale FROM storeSale GROUP BY productName, year) SalePoint , (SELECT searchWord, year, sum(searchCount)*0.1 as yearSearch FROM search GROUP BY searchWord, year) SearchPoint WHERE SalePoint.productName = SearchPoint.searchWord and SalePoint.year = SearchPoint.year ORDER BY yearPoint desc"))
			{
				finish_with_error(conn);
			}

			// Print Query Result
			result = mysql_store_result(conn);
			if (result == NULL)
			{
				finish_with_error(conn);
			}

			num_fields = mysql_num_fields(result);

			num_rows = mysql_num_rows(result);
			nr = 0;

			printf("\nSYSTEM : \n\n");
			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			printf("\n");

			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (i == 0)
					{
						int p = 0;
						while (field = mysql_fetch_field(result))
						{
							printf("\t|%20s", field->name);
							if(p == num_fields-1){
								printf("|\n");
								for(int m = 0 ; m < num_fields ; m++){
									printf("\t=====================");
								}
								printf("\n");
							}
							p++;
						}
					}
					printf("\t|%20s", row[i] ? row[i] : "NULL");
				}
				printf("|\n");
				nr++;
			}

			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			
			printf("\n");
			mysql_free_result(result);
			break;


		// Beer Info
		case 4:
			printf("\nSYSTEM : 맥주 이름을 검색하면 판매 맥주 정보를 알려줍니다.\n");
			printf("(not select : 1, previous menu : 0)\n맥주이름을 입력하세요 : ");
			cin.ignore();
			getline(cin, productName, '\n');
			input = not_select_or_previous_menu(productName);
			if (input == 0) break;
			if (input == 1) productName = "";

			printf("\n(SEARCH '%s') ...\n", productName);

			// Query
			sprintf_s(buf, "SELECT productGroup, beerType, alcohol, country, feeling, taste1, flavor1 FROM beerinfo NATURAL JOIN beercountry NATURAL JOIN beertaste NATURAL JOIN beerflavor NATURAL JOIN beerfeeling NATURAL JOIN storecatalog WHERE productName = '%s'", productName);

			if (mysql_query(conn, buf))
			{
				finish_with_error(conn);
			}

			// Print Query Result
			result = mysql_store_result(conn);
			if (result == NULL)
			{
				finish_with_error(conn);
			}

			num_fields = mysql_num_fields(result);

			num_rows = mysql_num_rows(result);
			nr = 0;

			printf("\nSYSTEM : \n\n");
			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			printf("\n");

			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (i == 0)
					{
						int p = 0;
						while (field = mysql_fetch_field(result))
						{
							printf("\t|%20s", field->name);
							if(p == num_fields-1){
								printf("|\n");
								for(int m = 0 ; m < num_fields ; m++){
									printf("\t=====================");
								}
								printf("\n");
							}
							p++;
						}
					}
					printf("\t|%20s", row[i] ? row[i] : "NULL");
				}
				printf("|\n");
				nr++;
			}

			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }

			printf("\n");
			mysql_free_result(result);
			break;


		// Slae Info
		case 5:
			printf("\nSYSTEM : 맥주 이름을 검색하면 판매 매장을 알려줍니다.\n");
			printf("(not select : 1, previous menu : 0)\n맥주이름을 입력하세요 : ");
			cin.ignore();
			getline(cin, productName, '\n');
			input = not_select_or_previous_menu(productName);
			if (input == 0) break;
			if (input == 1) productName = "";
			
			printf("\n(SEARCH '%s') ...\n", productName);

			// Query
			sprintf_s(buf, "SELECT storeName, ml, price, bootleOrCan FROM Storecatalog WHERE productName = '%s'", productName);
			if (mysql_query(conn, buf))
			{
				finish_with_error(conn);
			}

			// Print Query Result
			result = mysql_store_result(conn);
			if (result == NULL)
			{
				finish_with_error(conn);
				break;
			}

			num_fields = mysql_num_fields(result);

			num_rows = mysql_num_rows(result);
			nr = 0;

			printf("\nSYSTEM : \n\n");
			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			printf("\n");

			while (row = mysql_fetch_row(result))
			{
				for (int i = 0; i < num_fields; i++)
				{
					if (i == 0)
					{
						int p = 0;
						while (field = mysql_fetch_field(result))
						{
							printf("\t|%20s", field->name);
							if(p == num_fields-1){
								printf("|\n");
								for(int m = 0 ; m < num_fields ; m++){
									printf("\t=====================");
								}
								printf("\n");
							}
							p++;
						}
					}
					printf("\t|%20s", row[i] ? row[i] : "NULL");
				}
				printf("|\n");
				nr++;
			}

			for(int m = 0 ; m < num_fields ; m++){
		        if(m==0)
		            printf("\t+------------------------");
		        else if( m == num_fields-1)
		            printf("-------------------------+");
		        else
		            printf("------------------------");
		    }
			
			printf("\n");
			mysql_free_result(result);
			break;


		// Admin
		case 6:
			printf("\nSYSTEM : ");
			printf("(not select : 1, previous menu : 0)\n 맥주이름을 입력하세요 : ");
			cin.ignore();
			getline(cin, oldName, '\n');

			printf("\nSYSTEM : ");
			printf("(not select : 1, previous menu : 0)\n 변경할 이름을 입력하세요 : ");
			cin.ignore();
			getline(cin, newName, '\n');

			printf("\nSYSTEM : ");
			printf("%s --> %s\n", oldName, newName);

			// Query
			sprintf_s(buf, "UPDATE beerinfo SET productName = '%s' WHERE productName = '%s'", newName, oldName);
			if (mysql_query(conn, buf))
			{
				finish_with_error(conn);
			}
			break;
		}
	}

	mysql_close(conn);
	return 0;
}
