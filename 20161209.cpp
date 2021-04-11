#include <stdio.h>
#include "mysql.h"
#include <string.h>

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "20161209";
const char* db = "dbproject2";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}

		//My Database System
		int createstate = 0, insertstate = 0;
		FILE* Cfile = fopen("20161209_1.txt", "r");
		char createquery[570];
		while (!feof(Cfile)) {
			fgets(createquery, 570, Cfile);
			createstate = mysql_query(connection, createquery);
		}
		fclose(Cfile);

		FILE* Ifile = fopen("20161209_2.txt", "r");
		char insertquery[150];
		while (!feof(Ifile)) {
			fgets(insertquery, 150, Ifile);
			insertstate = mysql_query(connection, insertquery);
		}
		fclose(Ifile);

		FILE* Qfile = fopen("20161209_3.txt", "r");
		char query[16][400];
		for (int i = 0; i < 16; i++) {
			fgets(query[i], 400, Qfile);
			query[i][strlen(query[i]) - 1] = '\0';
			//printf("%s\n", query[i]);
		}
		fclose(Qfile);

		int T1, T2;
		while (1) {
			printf("\n------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE I\n");
			printf("\t2. TYPE II\n");
			printf("\t3. TYPE III\n");
			printf("\t4. TYPE IV\n");
			printf("\t5. TYPE V\n");
			printf("\t0. QUIT\n");
			printf("Which type of query? ");
			scanf("%d", &T1);

			if (T1 == 0) {
				printf("\nHave a Good Day :)");
				break;
			}
			else if (T1 == 1) {
				printf("\n---- TYPE I ----\n");
				while (1) {

					while (1) {
						char truck[6];
						printf("Input the number of truck : ");
						scanf("%s", truck); truck[strlen(truck)] = '\0';
						if (truck[0] == '0') break;

						//query
						int state = 0;
						char query1[200] = "";
						strcat(query1, query[0]); strcat(query1, truck); strcat(query1, "'");

						state = mysql_query(connection, query1);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							if (mysql_fetch_row(sql_result) == NULL) {
								printf("Truck %s is not destroyed.\n", truck); T2 = -1; break;
							}
							mysql_free_result(sql_result);
						}
						//if there exists crash

						while (1) {
							printf("\n---- Subtypes in TYPE I ----\n");
							printf("\t1. TYPE I-1\n");
							printf("\t2. TYPE I-2\n");
							printf("\t3. TYPE I-3\n");
							printf("Which type of query? ");
							scanf("%d", &T2);

							if (T2 == 0) break;
							else if (T2 == 1) {
								printf("\n** Find all customers who had a package on the truck at the time of the crash. **\n");
								printf("Customer Name: ");

								//query
								int state1 = 0;
								char query11[400] = "";
								strcat(query11, query[1]); strcat(query11, truck); strcat(query11, "'");

								state1 = mysql_query(connection, query11);
								if (state == 0) {
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
										printf("%s ", sql_row[0]);
									}
									mysql_free_result(sql_result);
								}printf("\n");
								//print
							}
							else if (T2 == 2) {
								printf("** FInd all recipients who had a package on that truck at the time of the crash **\n");
								printf("Recipient Name: ");

								//query
								int state2 = 0;
								char query12[400] = "";
								strcat(query12, query[2]); strcat(query12, truck); strcat(query12, "'");

								state2 = mysql_query(connection, query12);
								if (state == 0) {
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
										printf("%s ", sql_row[0]);
									}
									mysql_free_result(sql_result);
								}printf("\n");
								//print
							}
							else if (T2 == 3) {
								printf("** Find the last successful delivery by that truck prior to the crash **\n");
								printf("Last Successful Delivery\n");
								
								//query
								int state3 = 0;
								char query13[520] = "";
								strcat(query13, query[3]); strcat(query13, truck); strcat(query13, query[4]);

								state3 = mysql_query(connection, query13);
								if (state == 0) {
									sql_result = mysql_store_result(connection);
									while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
										printf(" Shipment: %s\n Time: %s\n From %s To %s\n",
											sql_row[0], sql_row[1], sql_row[3], sql_row[2]);
									}
									mysql_free_result(sql_result);
								}printf("\n");
								//print
							}
						}
						if (T2 == 0) break;
					}
					if (T2 == 0) break;
				}
			}
			else if (T1 == 2) {
				printf("\n---- TYPE II ----\n");
				while (1) {
					char year[5];
					printf("** Find the customer who has shipped the most packages in certain year **\n");
					printf("Which year? ");
					scanf("%s", year);
					if (year[0] == '0') break;

					printf("Customer Name : ");

					//query
					int state = 0;
					char query2[480] = "";
					strcat(query2, query[5]); strcat(query2, year); strcat(query2, query[6]);

					state = mysql_query(connection, query2);
					if (state == 0) {
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("%s ", sql_row[0]);
						}
						mysql_free_result(sql_result);
					}printf("\n");

					//print
				}
			}
			else if (T1 == 3) {
				printf("\n---- TYPE III ----\n");
				printf("** Find the customer who has spent the most money on shipping in the past certain year **\n");
				while (1) {
					char year[5];
					printf("Which year? ");
					scanf("%s", year);
					if (year[0] == '0') break;

					printf("Customer Name : ");

					//query
					int state = 0;
					char query3[560] = "";
					strcat(query3, query[7]); strcat(query3, year); strcat(query3, query[8]);

					state = mysql_query(connection, query3);
					if (state == 0) {
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("%s ", sql_row[0]);
						}
						mysql_free_result(sql_result);
					}printf("\n");

					//print
				}
			}
			else if (T1 == 4) {
				printf("\n---- TYPE IV ----\n");
				printf("** Find those packages that were not delivered within the promised time **\n");

				//query
				int state = 0;

				state = mysql_query(connection, query[9]);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("%s ", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}printf("\n");
				//print
			}
			else if (T1 == 5) {

				printf("\n---- TYPE V ----\n");
				printf("** Generate the bill for each customer for the past certain month **\n");
				while (1) {

					char billname[40] = "bill_";
					char month[7], name[20];
					printf("Customer Name: "); scanf("%s", name); name[strlen(name)] = '\0';
					if (name[0] == '0') break;
					printf("Which month(YYYY-MM)? "); scanf("%s", month);

					printf("Generating Bill..\n");

					strcat(billname, month); strcat(billname, name); strcat(billname, ".txt");
					FILE* bill = fopen(billname, "w");
					month[4] = '/';

					///query
					char query51[410] = "";
					strcat(query51, query[10]); strcat(query51, name);
					strcat(query51, query[11]); strcat(query51, month); strcat(query51, query[12]);

					int state1 = 0; bool isnull = true;

					state1 = mysql_query(connection, query51);
					if (state1 == 0) {
						sql_result = mysql_store_result(connection);
						fprintf(bill, "* Bill on %s *\nCustomer: %s\n", month, name);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							fprintf(bill, "Address:  %s\nAmount:   %s won\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
					char query52[530] = "";
					strcat(query52, query[13]); strcat(query52, name);
					strcat(query52, query[14]); strcat(query52, month);
					strcat(query52, query[15]);
					int state2 = 0;

					state2 = mysql_query(connection, query52);
					if (state1 == 0) {
						sql_result = mysql_store_result(connection);
						fprintf(bill, "\n* Bill by packages *\n");
						fprintf(bill, " Code     |Receipt | Details                     | Type          | Amount | Payment    | ISSUE TIME   | TIMELINE");
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							fprintf(bill, "\n %s | %6s | %25s | %13s | %swon | %11s | %s | %s",
								sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6], sql_row[7]);
						}
						mysql_free_result(sql_result);
					}printf("\n");

					fclose(bill);

					printf("Generation Completed\n");
				}
			}
		}
		FILE* Dfile = fopen("20161209_4.txt", "r");
		char dropquery[25];
		while (!feof(Dfile)) {
			fgets(dropquery, 25, Ifile);
			insertstate = mysql_query(connection, dropquery);
		}
		fclose(Dfile);


		mysql_close(connection);
	}

	return 0;
}