import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="App">
      Hello
    </div>
  );
}

function ButtonComponent() {
  const[isRed, setisRed] = useState(false);

  const style = {
    color: isRed ? "red": "black";
  }


}
export default App;
