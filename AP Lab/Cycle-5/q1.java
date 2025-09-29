package pack1;
import java.util.Scanner;
class Teacher{
	String name;
	String dept;
	String posDept;
	void readTeacher(){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter name of Teacher:");
		name = sc.nextLine();
		System.out.println("Enter name of Department:");
		dept = sc.nextLine();
		System.out.printf("Enter position of %s:", name);
		posDept = sc.nextLine();
	}
}
class Course{
	String name;
	String prog;
	int credits;
	void readTeacher(){
		Scanner sc = new Scanner(System.in);
		name = sc.nextLine();
		prog = sc.nextLine();
		credits = sc.nextInt();
	}
}
