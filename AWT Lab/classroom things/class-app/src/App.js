import { useState } from 'react';
import './App.css';

function App() {
  return (
    <div className="App">
      Hello
      <Question1 />
      <Question2 />
    </div>
  );
}

function Question1() {
  const [isRed, setisRed] = useState(false);

  const style = {
    color: isRed ? "red" : "black"
  };

  function handleClick() {
    setisRed(!isRed);
  }

  return (
    <div>
      <p style={style}>Button</p>
      <button onClick={handleClick}>Toggle Color</button>
    </div>
  );
}

function Question2() {
    const [count, setCount] = useState(0);

    return (
        
    )

}
export default App;
