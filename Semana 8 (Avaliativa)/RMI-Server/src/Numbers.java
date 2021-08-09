
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Numbers extends UnicastRemoteObject implements NumbersInterface {

	//A IDE solicita uma ID, mas caso não queira usar não tem problema.
	private static final long serialVersionUID = 8634373378347831458L;

	public Numbers() throws RemoteException {
	}

	/*
	 * Um número é par quando o dividimos por dois e seu resto é zero.
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
	 * Um número é impar quando, na divisão por dois, o resto é diferente de zero.
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
	 * Os números primos são os números naturais que podem ser divididos por apenas
	 * dois fatores: o número um e ele mesmo.
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
	 * Um número natural é composto quando tem mais de dois divisores naturais
	 * distintos. Todo o número inteiro não-primo e diferente de 1 é composto.
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
	 * Um número perfeito é um número natural para o qual a soma de todos os seus
	 * divisores naturais próprios é igual ao próprio número.
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
