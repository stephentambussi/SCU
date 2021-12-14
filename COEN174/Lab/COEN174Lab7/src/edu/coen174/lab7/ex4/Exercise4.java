package edu.coen174.lab7.ex4;

public class Exercise4 {

	public static void main(String[] args) {
		CustOrder order1 = new OnlineOrder();
		order1.processOrder(true);
		
		CustOrder order2 = new InStoreOrder();
		order2.processOrder(false);
	}

}

class OnlineOrder extends CustOrder {
	public void deliverOrder() {
		System.out.println("Order will be delivered on the shown date");
	}

	public void okToGiftWrap(boolean giftWrap) {
		if(giftWrap)
			System.out.println("Will be gift-wrapped");
	}

	public void makePayment() {
		System.out.println("Make payment by Credit Card");
	}

	public void selectItem() {
		System.out.println("Select the item");
		System.out.println("Select the delivery address");
	}
}

class InStoreOrder extends CustOrder {
	public void deliverOrder() {
		System.out.println("Order delivered to the Customer at the Counter");
	}

	public void okToGiftWrap(boolean giftWrap) {
		if(giftWrap)
			System.out.println("Will be gift-wrapped");
	}

	public void makePayment() {
		System.out.println("Make payment by Cash or Credit Card");
	}

	public void selectItem() {
		System.out.println("Item scanned at the Register");
	}
}