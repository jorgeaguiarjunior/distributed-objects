
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface NumbersInterface extends Remote {

	public int quantidadeDeNumerosPares(Integer inicio, Integer fim) throws RemoteException;

	public int quantidadeDeNumerosImpares(Integer inicio, Integer fim) throws RemoteException;

	public int quantidadeDeNumerosPrimos(int inicio, int fim) throws RemoteException;

	public int quantidadeDeNumerosCompostos(int inicio, int fim) throws RemoteException;

	public int quantidadeDeNumerosPerfeitos(int inicio, int fim) throws RemoteException;

}
