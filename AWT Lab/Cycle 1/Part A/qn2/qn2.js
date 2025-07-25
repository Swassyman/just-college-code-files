class Student {
  constructor(name, rollNo, mark1, mark2) {
    (this.name = name),
      (this.rollNo = rollNo),
      (this.mark1 = mark1),
      (this.mark2 = mark2);
  }
  getAverage() {
    document.writeln(
      this.name +
        " got " +
        (this.mark2 + this.mark1) / 2 +
        "% for her final exam."
    );
  }
}
