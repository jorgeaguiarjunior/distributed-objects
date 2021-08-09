/*
 * Para funcionar é necessário criar os stubs (já estão criados);
 * Caso os stubs não estejam criados, basta abrir o cmd e ir no diretorio da classe que implementa a interface NumbersInterface, ou seja, a classe Numbers
 * e usar o comando "rmic NomeDaClasseQueImplementa", ou seja "rmic Numbers";
 * Instalar os stubs no cliente, basta copiar os arquivos e colar nos arquivos do cliente;
 * Adicionar a interface NumbersInterface no cliente, basta copiar a interface e colar no cliente;
 * Executar o comando "RMIRegistry" no diretorio do servidor, usando o cmd;
 * Por ultimo basta executar o servidor antes do cliente.
 */
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Program {

	public static void main(String[] args) throws RemoteException {
		NumbersInterface numbers = new Numbers();
		
		try {
			Naming.rebind("num", numbers);
			System.out.println("Servidor em execução. " + LocateRegistry.getRegistry());
		} catch (RemoteException e) {
			e.printStackTrace();
		} catch (MalformedURLException e) {
			e.printStackTrace();
		}
	}

}
