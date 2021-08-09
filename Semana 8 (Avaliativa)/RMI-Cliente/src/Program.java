import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public class Program {

	public static void main(String[] args) {

		try {
			NumbersInterface numb = (NumbersInterface) Naming.lookup("rmi://192.168.1.108/num");
			System.out.println("Numeros pares: " + numb.quantidadeDeNumerosPares(1, 1000));
			System.out.println("Numeros impares: " + numb.quantidadeDeNumerosImpares(1, 1000));
			System.out.println("Numeros primos: " + numb.quantidadeDeNumerosPrimos(1, 1000));
			System.out.println("Numeros perfeitos: " + numb.quantidadeDeNumerosPerfeitos(1, 1000));
			System.out.println("Numeros compostos: " + numb.quantidadeDeNumerosCompostos(1, 1000));
		} catch (MalformedURLException | RemoteException | NotBoundException e) {
			e.printStackTrace();
		}

	}

}
