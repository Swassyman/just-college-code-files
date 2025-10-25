import logo from "./logo.svg";
import "./App.css";
import { useState } from "react";
import styles from "./button.module.css";
function App() {
  return (
    <div className="App">
      <header className="App-header">
        <ButtonComponent />
      </header>
    </div>
  );
}

function ButtonComponent() {
  const [count, setcount] = useState(0);

  const buttonStyle = {
    backgroundColor: "crimson",
    color: "white",
    padding: "10px 20px",
    border: "none",
    borderRadius: "8px",
    cursor: "pointer",
  };

  function handleClick() {
    setcount(count + 1);
  }
  return (
    <div className="button">
      <button
        style={buttonStyle}
        className={styles.button}
        onClick={handleClick}
      >
        Click please
      </button>
      <p> You clicked {count} times</p>
    </div>
  );
}
export default App;
