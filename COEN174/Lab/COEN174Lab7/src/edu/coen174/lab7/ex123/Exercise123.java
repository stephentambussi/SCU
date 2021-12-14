package edu.coen174.lab7.ex123;

public class Exercise123 
{
	public static void main(String[] args)
	{
		Employee emp1 = new Employee("Dan Stellar", "007");
		System.out.println(emp1); //This calls the toString()
		
		Billable partEmp = new PartTimeEmployee("D.Smith", "123", 20.00, 30, 10.00, "programming");
		
		Billable org = new Organization("ABCOrg", 100.00, "ProjectManagement");
		
		System.out.println(partEmp.getSkill());
		System.out.println(org.getSkill());
		System.out.println(partEmp.getBillingRate());
		System.out.println(org.getBillingRate());
		//Can only call getSkill or getBillingRate because objects are of type Billable, not org or emp
	}
}

class Employee 
{
	private String name;
	private String empId;
	private double salary;
	public Employee() //default constructor
	{
		
	}
	public Employee(String name, String empId) {
		this.name = name;
		this.empId = empId;
	}
	public double getSalary() {
		return salary;
	}
	public void setSalary(double salary) {
		this.salary = salary;
	}
	@Override
	public String toString() {
		return "Employee [name=" + name + ", empId=" + empId + "]";
	}
}

class PartTimeEmployee extends Employee implements Billable
{
	private double hrlyPay;
	private int hrsWorked;
	private double billingRate;
	private String skill;
	public PartTimeEmployee() //default constructor
	{
		
	}
	public PartTimeEmployee(String name, String empId, double hrlyPay, int hrsWorked, double billingRate, String skill) {
		super(name, empId); //calls the superclass, Employee, constructor
		this.hrlyPay = hrlyPay;
		this.hrsWorked = hrsWorked;
		this.billingRate = billingRate;
		this.skill = skill;
	}
	public double getHrlyPay() {
		return hrlyPay;
	}
	public int getHrsWorked() {
		return hrsWorked;
	}
	public double getBillingRate() {
		return billingRate;
	}
	public String getSkill() {
		return skill;
	}
}

class Organization implements Billable 
{
	private String orgName;
	private double billingRate;
	private String skill;
	public Organization(String orgName, double billingRate, String skill) { //constructor
		this.orgName = orgName;
		this.billingRate = billingRate;
		this.skill = skill;
	}
	public String getOrgName() {
		return orgName;
	}
	public double getBillingRate() {
		return billingRate;
	}
	public String getSkill() {
		return skill;
	}
	
}