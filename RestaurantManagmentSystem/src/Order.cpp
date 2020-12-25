#include "Order.h"

size_t Order::current_id = NULL;

void Order::setMeal(std::shared_ptr<Meal> meal) { this->meal = meal; }
std::shared_ptr<Meal> Order::getMeal() const { return this->meal; }
bool Order::operator==(const Order& order) const { return this->getID() == order.getID(); }
void Order::setTableNo(const std::string& table_no) { this->table_no = table_no; }
std::string Order::getTableNo() const { return this->table_no; }
std::ostream& operator<<(std::ostream& out, const Order& order)
{
	out << "###################################" << std::endl;
	out << "Table no: " << order.getTableNo() << std::endl;
	out << "Meal: " << order.getMeal()->getName() << std::endl;
	return out;
}
void Order::fullInfo() const
{
	std::cout << "#################################" << std::endl;
	std::cout << "Table no: " << getTableNo() << std::endl;
	std::cout << "Meal name: " << getMeal()->getName() << std::endl;
	std::cout << "Amount: " << getAmount() << std::endl;
	getMeal()->printRecipe();
}