#pragma once
#include "Base.h"
#include "Order.h"
#include <list>

class Table : public Base
{
	std::string table_no;
	std::list<std::shared_ptr<Order>> orders;
	std::string notfFromKitchen;
public:
	static size_t current_id;
	Table() : table_no(""), notfFromKitchen("") {}

	Table(const std::string& table_no) : Base(++current_id) {
		setTableNo(table_no);
	}

	void setTableNo(const std::string& table_no);
	void setNotfFromKitchen(const std::string& message);

	std::string getTableNo()const;
	std::string getNotfFromKitchen() const;
	std::list<std::shared_ptr<Order>> getOrders() const;
	std::shared_ptr<Order>& getOrder(const size_t& id);

	void addOrder(const std::shared_ptr<Order>& order);
	void deleteOrder(const std::shared_ptr<Order>& order);
	void deleteAllOrders();
	void showOrders() const;
	bool operator==(const Table&) const;
};