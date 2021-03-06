#pragma once
#include <strsafe.h>
#include <Windows.h>
#include <iostream>
#include <vector>

#define MainScreenM Screen::MainScreen
#define LoginScreenM Screen::MainScreen::LoginScreen
#define AdminScreenM Screen::MainScreen::AdminScreen
#define KitchenScreenM Screen::MainScreen::AdminScreen::KitchenScreen
#define OrderControlScreenM Screen::MainScreen::AdminScreen::KitchenScreen::OrderControlScreen
#define DatabaseScreenM Screen::MainScreen::AdminScreen::DatabaseScreen
#define AdminControlScreenM Screen::MainScreen::AdminScreen::DatabaseScreen::AdminsScreen
#define StockScreenM Screen::MainScreen::AdminScreen::DatabaseScreen::StockScreen
#define MealScreenM Screen::MainScreen::AdminScreen::DatabaseScreen::MealsScreen
#define NotificationScreenM Screen::MainScreen::AdminScreen::DatabaseScreen::NotificationsScreen
#define ClientScreenM Screen::MainScreen::ClientScreen
#define TableScreenM Screen::MainScreen::ClientScreen::TableScreen
#define OrderScreenM Screen::MainScreen::ClientScreen::TableScreen::OrderScreen

class Screen
{
public:
	struct Button
	{
		short id;
		COORD leftBottom;
		COORD rightTop;

		Button() {};
		Button(const short& id, const COORD& leftBottom, const COORD& rightTop) : id(id), leftBottom(leftBottom), rightTop(rightTop) {}
	};

	static void printExit(const bool& mouseOver = false);
	static void printBack(const bool& mouseOver = false);
	static void printLogout(const bool& mouseOver = false);
	static void printOut(const bool& mouseOver = false);

	static COORD COORDINATE;
	static void printButton(const std::string& text, COORD& coo, const unsigned short& length = 24);
	static void printPanel(COORD leftTop, COORD rightBottom);
	static size_t getButtonIdByCoordinate(const COORD& coo, const std::vector<Button> &buttons);
	
	class MainScreen {
	public:
		static size_t mouseOver;
		static std::vector<std::string> options;
		static std::vector<Button> buttons;

		static void print();
		static size_t start();
		static void load();

		class LoginScreen
		{
		public:
			static size_t mouseOver;
			static std::vector<std::string> options;
			static std::vector<Button> buttons;

			static void print();
			static size_t start();
			static void load();
		};

		class AdminScreen {
		public:
			static size_t selected;
			static size_t mouseOver;
			static std::vector<std::string> options;
			static std::vector<Button> buttons;

			static void print();
			static size_t start();
			static void load();

			class KitchenScreen {
			public:
				static size_t selected;
				static size_t mouseOver;
				static std::vector<std::string> options;
				static std::vector<Button> buttons;

				static void print();
				static size_t start();
				static void load();

				class OrderControlScreen {
				public:
					static size_t selected;
					static size_t mouseOver;
					static std::vector<std::string> options;
					static std::vector<Button> buttons;

					static void print();
					static size_t start();
					static void load();
				};
			};

			class DatabaseScreen {
			public:
				static size_t selected;
				static size_t mouseOver;
				static std::vector<std::string> options;
				static std::vector<Button> buttons;

				static void print();
				static size_t start();
				static void load();
				class AdminsScreen {
				public:
					static size_t selected;
					static size_t mouseOver;
					static std::vector<std::string> options;
					static std::vector<Button> buttons;

					static void print();
					static size_t start();
					static void load();
				};

				class MealsScreen {
				public:
					static size_t selected;
					static size_t mouseOver;
					static std::vector<std::string> options;
					static std::vector<Button> buttons;

					static void print();
					static size_t start();
					static void load();
				};

				class NotificationsScreen {
				public:
					static size_t selected;
					static size_t mouseOver;
					static std::vector<std::string> options;
					static std::vector<Button> buttons;

					static void print();
					static size_t start();
					static void load();
				};

				class StockScreen {
				public:
					static size_t selected;
					static size_t mouseOver;
					static std::vector<std::string> options;
					static std::vector<Button> buttons;

					static void print();
					static size_t start();
					static void load();
				};
			};
		};

		class ClientScreen {
		public:
			static size_t mouseOver;
			static std::vector<Button> buttons;

			static void printTables(const short& table_count);
			static size_t start(const short& table_count);
			static void load(const short& table_count);

			class TableScreen {
			public:
				static size_t mouseOver;
				static std::vector<std::string> options;
				static std::vector<Button> buttons;

				static void print();
				static size_t start();
				static void load();

				class AboutScreen {
				public:
					static size_t selected;

					static short print();
				};

				class OrderScreen {
				public:
					static size_t mouseOver;
					static std::vector<std::string> options;
					static std::vector<Button> buttons;

					static void print();
					static size_t start();
					static void load();
				};
			};
		};
	};

	class Menu
	{
	public:
		static void printMenu(const std::vector<std::string>& options, const unsigned short& selected);
		static void printMenuAxis(const std::vector<std::string>& options, const unsigned short& selected);
	};
};