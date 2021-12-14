package edu.coen174.lab7.ex4;

public abstract class CustOrder {
	final public void processOrder(boolean giftWrap) { //final means that method cannot be overridden by subclasses
		//Select Item
		selectItem();
		
		//Make Payment
		makePayment();
		
		//Check if giftwrap is required
		okToGiftWrap(giftWrap);
		
		//deliverOrder
		deliverOrder();
	}
	public abstract void selectItem();
	public abstract void makePayment();
	public abstract void okToGiftWrap(boolean giftWrap);
	public abstract void deliverOrder();
}