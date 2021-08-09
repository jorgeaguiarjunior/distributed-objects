
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Numbers extends UnicastRemoteObject implements NumbersInterface {

	//A IDE solicita uma ID, mas caso n�o queira usar n�o tem problema.
	private static final long serialVersionUID = 8634373378347831458L;

	public Numbers() throws RemoteException {
	}

	/*
	 * Um n�mero � par quando o dividimos por dois e seu resto � zero.
	 */
	@Override
	public int quantidadeDeNumerosPares(Integer inicio, Integer fim) throws RemoteException {
		int qtd = 0;
		for (int i = inicio; i <= fim; i++) {
			if (i % 2 == 0) {
				qtd++;
			}
		}
		return qtd;
	}

	/*
	 * Um n�mero � impar quando, na divis�o por dois, o resto � diferente de zero.
	 */
	@Override
	public int quantidadeDeNumerosImpares(Integer inicio, Integer fim) throws RemoteException {
		int qtd = 0;
		for (int i = inicio; i <= fim; i++) {
			if (i % 2 != 0) {
				qtd++;
			}
		}
		return qtd;
	}

	/*
	 * Os n�meros primos s�o os n�meros naturais que podem ser divididos por apenas
	 * dois fatores: o n�mero um e ele mesmo.
	 */
	@Override
	public int quantidadeDeNumerosPrimos(int inicio, int fim) throws RemoteException {
		int valida = 0;
		int qtd = 0;
		for (int i = inicio; i <= fim; i++) {
			for (int j = 2; j < i; j++) {
				if (i % j == 0) {
					valida++;
				}
			}
			if (valida == 0 && i != 1) {
				qtd++;
			}
			valida = 0;
		}
		return qtd;
	}

	/*
	 * Um n�mero natural � composto quando tem mais de dois divisores naturais
	 * distintos. Todo o n�mero inteiro n�o-primo e diferente de 1 � composto.
	 */
	@Override
	public int quantidadeDeNumerosCompostos(int inicio, int fim) throws RemoteException {
		int valida = 0;
		int qtd = 0;

		for (int i = inicio; i <= fim; i++) {
			for (int j = 2; j < i; j++) {
				if (i % j == 0) {
					valida++;
				}
			}
			if (valida != 0 && i != 1) {
				qtd++;
			}
			valida = 0;
		}
		return qtd;
	}

	/*
	 * Um n�mero perfeito � um n�mero natural para o qual a soma de todos os seus
	 * divisores naturais pr�prios � igual ao pr�prio n�mero.
	 */
	@Override
	public int quantidadeDeNumerosPerfeitos(int inicio, int fim) throws RemoteException {
		int soma = 0;
		int qtd = 0;

		for (int i = inicio; i < fim; i++) {
			for (int j = i - 1; j > 0; j--) {
				if (i % j == 0) {
					soma += j;
				}
			}
			if (soma == i) {
				qtd++;
			}
			soma = 0;
		}
		return qtd;
	}

}
