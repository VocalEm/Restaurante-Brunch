#include<windows.h>
#include "resource.h"
#include<string>
#include<stdlib.h>
#include<ctime>
#include<fstream>
using namespace std;

int tipoUs = 0;
//variables
HINSTANCE hGlobalIdentificador;
wchar_t* rutaImagenEnDisco = new wchar_t[255];
int forCant = 0;
int forPromo = 0;
//fecha
int getMonth();
int getYear();
int getDay();

int iYear = getYear();
int iMonth = getMonth();
int iDay = getDay();

string yearS = to_string(iYear);
string monthS = to_string(iMonth);
string dayS = to_string(iDay);
string formatoFechaActual =  dayS + "/" + monthS + "/" + yearS;
//fecha


//usuarios
struct usuarios
{
	int id = 1;
	string nombre;
	string user;
	string password;
	string sucursal;
	int tipoUsuario = 0; //1 admin, 0 user
	usuarios* sig = NULL;
	usuarios* ant = NULL;
	char RutaImagen[MAX_PATH];
};
int contadorUs = 0;
usuarios* inicioListaUser = NULL;
usuarios* finListaUser = NULL;
usuarios* auxUs = NULL;
usuarios* auxUsM = NULL;
usuarios* auxEliminar = NULL;
void escribirBinUsuario();
void leerBinUsuario();
//usuarios

//clientes
struct clientes
{
	int id = 0;
	string nombre;
	string correo;
	string sucursal;
	string fecha;
	int puntos = 0;
	int dineroGastado = 0;
	clientes* sig = NULL;
	clientes* ant = NULL;
};
int contadorClientes = 1;
clientes* inicioListaClientes = NULL;
clientes* finListaClientes = NULL;
clientes* auxClientes = NULL;
clientes* auxClientesEliminar = NULL;
clientes** arreglo;
string nombreClienteGuardar;
int cantidadClientes = 0;

int contadorC = 0;
void escribirBinClientes();
void leerBinClientes();
//clientes

//sucursales
struct sucursales
{
	int id = 0;
	string nombre;
	string direccion;
	sucursales* sig = NULL;
	sucursales* ant = NULL;
};
int contadorSu = 1;
sucursales* inicioListaSucursal = NULL;
sucursales* finListaSucursal = NULL;
sucursales* auxSu = NULL;
sucursales* auxSuEliminar = NULL;
void escribirBinSucursales();
void leerBinSucursales();
//sucursales

//promos
struct promos 
{
	int id = 0;
	string nombre;
	int puntosReq = 0;
	float descuento = 0;
	int estatus = 0;
	int canjeadasContador = 0;
	promos* sig = NULL;
	promos* ant = NULL;
};
int contadorPromo = 1;
promos* inicioListaPromos = NULL;
promos* finListaPromos = NULL;
promos* auxP = NULL;
promos* auxPEliminar = NULL;
promos** arregloPromo;
int cantidadPromos = 0;
void escribirBinPromos();
void leerBinPromos();
//promos
//variable

//funciones

usuarios* agregarNodoUsuario(string nombre, string user, string password, string sucursal, int tipoUsuario);
sucursales* agregarNodoSucursal(string nombre, string direccion);
clientes* agregarNodoClientes(string nombre, string correo, string sucursal, string fecha);
void sucursalDefault();
promos* agregarNodoPromos(string nombre, int puntos, int idescuento, int estatus);
void swap(clientes** a, clientes** b);
int partition(clientes** arreglo, int low, int high);
void quicksort(clientes** arreglo, int low, int high);
void cargandoArregloPromo();
void swapDinero(clientes** a, clientes** b);
int partitionDinero(clientes** arreglo, int low, int high);
void quicksortDinero(clientes** arreglo, int low, int high);
//funciones

//CANJEE
INT_PTR CALLBACK fnDlgCanjear1(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
//CANJEE

/// /// /// ventanas
INT_PTR CALLBACK fnDlgMenu(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgInicioSesion(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgRegistrar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
//////
//VENTA
INT_PTR CALLBACK fnDlgPromoVenta(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
//VENTA
//prom;
INT_PTR CALLBACK fnDlgPromoModificar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgPromoMostrar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgPromoAgregar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgPromoEliminar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
//promo
//clientes
INT_PTR CALLBACK fnDlgClientesModificar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgClientesMostrar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgClientesAgregar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgClientesEliminar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
//clientes
//sucursales
INT_PTR CALLBACK fnDlgSucursalModificar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgSucursalMostar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgSucursalAgregar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgSucursalEliminar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
//sucursales
//usuarios ventanas
INT_PTR CALLBACK fnDlgUsuarioEliminar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgUsuarioModificar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgUsuarioMostrar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgUsuarioAgregar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
//usuarios ventanas
INT_PTR CALLBACK fnDlgMenu(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgInicioSesion(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
/// /// /// ventanas

//REPORTES
INT_PTR CALLBACK fnDlgReportePuntos(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgReportePromos(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fnDlgReporteDinero(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam);
//REPOTRES

int WINAPI wWinMain (HINSTANCE hIdentificador, HINSTANCE hProgramaPrevio, PWSTR pArgumentosLineaComandos, int nTipoMuestraVentana)
{
	hGlobalIdentificador = hIdentificador;
	leerBinUsuario();
	leerBinClientes();
	leerBinPromos();
	leerBinSucursales();
	//sucursalDefault();

	HWND dlgInicioSesion = CreateDialogW(hIdentificador, MAKEINTRESOURCE(DLG_INICIOSESION), NULL, fnDlgInicioSesion);
	ShowWindow(dlgInicioSesion, SW_SHOW);

	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	escribirBinClientes();
	escribirBinUsuario();
	escribirBinSucursales();
	escribirBinPromos();

	return 0;
	
}

//funciones
void sucursalDefault()
{
	agregarNodoSucursal("Default", "Default");
}
usuarios* agregarNodoUsuario(string nombre, string user, string password, string sucursal, int tipoUsuario, wchar_t* rutaImagenEnDisco)
{

	usuarios* usuarioN = new usuarios;
	usuarioN->sig = NULL;
	usuarioN->ant = NULL;

	wstring ws = wstring(rutaImagenEnDisco);
	string imagen(ws.begin(), ws.end());
	strcpy_s(usuarioN->RutaImagen, imagen.c_str());

	if (inicioListaUser == NULL)
	{

		inicioListaUser = usuarioN;
		finListaUser = usuarioN;

		usuarioN->nombre = nombre;
		usuarioN->user = user;
		usuarioN->password = password;
		usuarioN->tipoUsuario = tipoUsuario;
		usuarioN->sucursal = sucursal;
		
	}

	else
	{
		finListaUser->sig = usuarioN;
		usuarioN->ant = finListaUser;
		finListaUser = usuarioN;

		usuarioN->nombre = nombre;
		usuarioN->user = user;
		usuarioN->password = password;
		usuarioN->tipoUsuario = tipoUsuario;
		usuarioN->sucursal = sucursal;
	}

	int id = 1;
	auxUsM = inicioListaUser;
	while (auxUsM != NULL)
	{
		auxUsM->id = id++;
		auxUsM = auxUsM->sig;
	}

	return usuarioN;
}
sucursales* agregarNodoSucursal(string nombre, string direccion)
{


	sucursales* sucursal = new sucursales;
	sucursal->nombre = nombre;
	sucursal->direccion = direccion;

	if (inicioListaSucursal == NULL)
	{
		inicioListaSucursal = sucursal;
		finListaSucursal = sucursal;
	}

	else
	{
		finListaSucursal->sig = sucursal;
		sucursal->ant = finListaSucursal;
		finListaSucursal = sucursal;

	}

	int id = 1;
	auxSu = inicioListaSucursal;
	while (auxSu != NULL)
	{
		auxSu->id = id++;
		auxSu = auxSu->sig;
	}


	return sucursal;
}
clientes* agregarNodoClientes(string nombre, string correo, string sucursal, string fecha)
{
	clientes* cliente = new clientes;


	if (inicioListaClientes == NULL)
	{
		inicioListaClientes = cliente;
		finListaClientes = cliente;

		cliente->id = contadorClientes++;
		cliente->nombre = nombre;
		cliente->correo = correo;
		cliente->sucursal = sucursal;
		cliente->fecha = fecha;
		cliente->dineroGastado = 0;
	}

	else
	{
		finListaClientes->sig = cliente;
		cliente->ant = finListaClientes;
		finListaClientes = cliente;

		cliente->id = contadorClientes++;
		cliente->nombre = nombre;
		cliente->correo = correo;
		cliente->sucursal = sucursal;
		cliente->fecha = fecha;
	}

	int id = 1;
	auxClientes = inicioListaClientes;
	while (auxClientes != NULL)
	{
		auxClientes->id = id++;
		auxClientes = auxClientes->sig;
	}

	return cliente;
}
promos* agregarNodoPromos(string nombre, int puntos, int idescuento, int estatus)
{
	float num = idescuento;
	num = num / 100;
	promos* promo = new promos;
	promo->nombre = nombre;
	promo->puntosReq = puntos;
	promo->descuento = num;
	promo->estatus = estatus;
	promo->canjeadasContador = 0;

	if (inicioListaPromos == NULL)
	{
		inicioListaPromos = promo;
		finListaPromos = promo;
	}

	else
	{
		finListaPromos->sig = promo;
		promo->ant = finListaPromos;
		finListaPromos = promo;
	}

	int id = 1;
	auxP = inicioListaPromos;
	while (auxP != NULL)
	{
		auxP->id = id++;
		auxP = auxP->sig;
	}

	return promo;
}


//VENTA
INT_PTR CALLBACK fnDlgPromoVenta(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	string formato;
	switch (uMensaje)
	{//sw

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, IDC_STATIC14, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_PROMOPUNTOSIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);


		SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSNOMBRE, "");
		SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSCORREO, "");
		SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSSUCURSAL, "");
		SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSFECHA, "");
		SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSCLIENTEPUNTOS, "");
		SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSID, "");
		SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSERROR, "");

		auxClientes = inicioListaClientes;
		while (auxClientes != NULL)
		{
			string cont = to_string(auxClientes->id);
			formato = cont + "- " + auxClientes->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTPPUNTOSCLIENTES);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxClientes);
			auxClientes = auxClientes->sig;
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//SW2

		case BTN_PAGREGARPUNTOS:
		{
			int exitoCliente = 0;
			char cventa[50], cid[50];

			GetDlgItemTextA(hDialogoActual, LBL_PPUNTOSID, cid, 50);
			string Sid(cid);
			GetDlgItemTextA(hDialogoActual, TXT_PPUNTOSVENTA, cventa, 50);
			string venta(cventa);

			if (venta.empty() || Sid.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSERROR, "Debe de elegir un cliente y introducir monto");
			}
			else if (stoi(venta) < 0)
			{
				SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSERROR, "Debe ser mayor a  0$ la venta");
			}

			else
			{
				auxClientes = inicioListaClientes;
				while (auxClientes != NULL && auxClientes->id != stoi(Sid))
				{
					auxClientes = auxClientes->sig;
				}
				
				if (auxClientes == NULL)
				{
					SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSERROR, "Debe de elegir un cliente y introducir monto");
				}
				else 
				{
					auxClientes->dineroGastado = auxClientes->dineroGastado + stoi(venta);
					auxClientes->puntos = auxClientes->puntos + (stoi(venta) / 10);
					int num = stoi(venta) / 10;
					string mensaje = "Al cliente " + auxClientes->nombre + " Se le otorgaron " + to_string(num) + " puntos por la compra de " + venta + "$";
					MessageBoxA(hDialogoActual, mensaje.c_str(), "Compra Exitosa", MB_OK);
				}
				
			}


		}
		break;

		case LBX_LISTPPUNTOSCLIENTES:
		{
			switch (HIWORD(wParam))
			{//SW3

			case CBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTPPUNTOSCLIENTES, LB_GETCURSEL, NULL, NULL);
				clientes* clientesListaMostrar = (clientes*)SendDlgItemMessage(hDialogoActual, LBX_LISTPPUNTOSCLIENTES, LB_GETITEMDATA, indice, NULL);
				int puntos = clientesListaMostrar->puntos;
				string sPuntos = to_string(puntos);
				string id = to_string(clientesListaMostrar->id);
				SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSID, id.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSNOMBRE, clientesListaMostrar->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSCORREO, clientesListaMostrar->correo.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSSUCURSAL, clientesListaMostrar->sucursal.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSFECHA, clientesListaMostrar->fecha.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_PPUNTOSCLIENTEPUNTOS, sPuntos.c_str());
			}
			break;

			}//SW3
		}
		break;

		case BTN_PSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//SW2
	}
	break;

	}//sw

	return FALSE;
}
//VENTA

//REPORTES

void cargandoArregloPromo()
{
	int i = 0;
	auxP = inicioListaPromos;
	while (auxP != NULL)
	{
		cantidadPromos++;
		auxP = auxP->sig;
	}

	arregloPromo = new promos * [cantidadPromos];

	auxP = inicioListaPromos;
	while (auxP != NULL)
	{
		arregloPromo[i] = auxP;
		auxP = auxP->sig;
		i++;
	}
}
void cargandoArreglo()
{
	int i = 0;
	auxClientes = inicioListaClientes;
	while (auxClientes != NULL)
	{
		cantidadClientes++;
		auxClientes = auxClientes->sig;
	}

	arreglo = new clientes * [cantidadClientes];

	auxClientes = inicioListaClientes;
	while (auxClientes != NULL)
	{
		arreglo[i] = auxClientes;
		auxClientes = auxClientes->sig;
		i++;
	}

}

void swap(clientes** a, clientes** b)
{
	clientes* temp = *a;
	*a = *b;
	*b = temp;
}
int partition(clientes** arreglo, int low, int high) {
	int pivot = arreglo[high]->puntos;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (arreglo[j]->puntos < pivot) {
			i++;
			swap(&arreglo[i], &arreglo[j]);
		}
	}
	swap(&arreglo[i + 1], &arreglo[high]);
	return (i + 1);
}
void quicksort(clientes** arreglo, int low, int high) 
{
	if (low < high)
	{
		int pivotIndex = partition(arreglo, low, high);
		quicksort(arreglo, low, pivotIndex - 1);
		quicksort(arreglo, pivotIndex + 1, high);
	}
}

void swapDinero(clientes** a, clientes** b)
{
	clientes* temp = *a;
	*a = *b;
	*b = temp;
}
int partitionDinero(clientes** arreglo, int low, int high) {
	int pivot = arreglo[high]->dineroGastado;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (arreglo[j]->dineroGastado < pivot) {
			i++;
			swapDinero(&arreglo[i], &arreglo[j]);
		}
	}
	swapDinero(&arreglo[i + 1], &arreglo[high]);
	return (i + 1);
}
void quicksortDinero(clientes** arreglo, int low, int high)
{
	if (low < high)
	{
		int pivotIndex = partitionDinero(arreglo, low, high);
		quicksortDinero(arreglo, low, pivotIndex - 1);
		quicksortDinero(arreglo, pivotIndex + 1, high);
	}
}

void swapPromos(promos** a, promos** b)
{
	promos* temp = *a;
	*a = *b;
	*b = temp;
}
int partitionPromos(promos** arregloPromos, int low, int high) {
	int pivot = arregloPromos[high]->canjeadasContador;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (arregloPromos[j]->canjeadasContador < pivot) {
			i++;
			swapPromos(&arregloPromos[i], &arregloPromos[j]);
		}
	}
	swapPromos(&arregloPromos[i + 1], &arregloPromos[high]);
	return (i + 1);
}
void quicksortPromos(promos** arregloPromos, int low, int high)
{
	if (low < high)
	{
		int pivotIndex = partitionPromos(arregloPromos, low, high);
		quicksortPromos(arregloPromos, low, pivotIndex - 1);
		quicksortPromos(arregloPromos, pivotIndex + 1, high);
	}
}



INT_PTR CALLBACK fnDlgCanjear2(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	auxClientes = inicioListaClientes;
	while (auxClientes != NULL && auxClientes->nombre != nombreClienteGuardar)
	{
		auxClientes = auxClientes->sig;
	}
	int puntosGuardados = 0;
	int num;
	switch (uMensaje)
	{//sw1
		
	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_CANJEARPROMOUS, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_CANJEARPROMO);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_CANJENOMBREPROMO, "");
		SetDlgItemTextA(hDialogoActual, LBL_CANJEPUNTOSPROMO, "");
		SetDlgItemTextA(hDialogoActual, LBL_CANJEDESCUENTOPROMO, "");
		SetDlgItemTextA(hDialogoActual, LBL_CANJEESTATUSPROMO, "");
		SetDlgItemTextA(hDialogoActual, LBL_CANJEDESCUENTOFINAL, "");
		SetDlgItemTextA(hDialogoActual, LBL_CANJEPUNTOSCLIENTE, to_string(auxClientes->puntos).c_str());
		SetDlgItemTextA(hDialogoActual, LBL_AVISOCANJEAR, "");
		SetDlgItemTextA(hDialogoActual, LBL_CANJEARPROMOID, "");

		


		auxP = inicioListaPromos;
		while (auxP != NULL)
		{
			string formato;
			formato = to_string(auxP->id) + " " + auxP->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTCANJEPROMO);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxP);
			auxP = auxP->sig;
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//SW2

		case BTN_CANJEARPROMO:
		{
			char cventa[50];
			char cPuntos[50];
			char cDescuento[50];
			char cid[3];
			char cEstatus[50];

			GetDlgItemTextA(hDialogoActual, TXT_VENTACANJE, cventa, 50);
			string venta(cventa);

			GetDlgItemTextA(hDialogoActual, LBL_CANJEARPROMOID, cid, 3);
			string id(cid);

			GetDlgItemTextA(hDialogoActual, LBL_CANJEPUNTOSPROMO, cPuntos, 50);
			string puntos(cPuntos);
			puntosGuardados = stoi(puntos);

			GetDlgItemTextA(hDialogoActual, LBL_CANJEESTATUSPROMO, cEstatus, 50);
			string estatus(cEstatus);

			GetDlgItemTextA(hDialogoActual, LBL_CANJEDESCUENTOPROMO, cDescuento, 50);
			string descuento(cDescuento);
			
			auxP = inicioListaPromos;
			while(auxP != NULL && auxP->id != stoi(id))
			{ 
				auxP = auxP->sig;
			}

			if (venta.empty() || puntos.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_AVISOCANJEAR, "Debe Ingresar la cantidad de venta y seleccionar una promocion");
			}

			else if (stoi(venta) < 0)
			{
				SetDlgItemTextA(hDialogoActual, LBL_AVISOCANJEAR, "Debe Ingresar una cantidad correcta");
			}
			
			else if ((auxClientes->puntos - stoi(puntos)) < 0)
			{
				SetDlgItemTextA(hDialogoActual, LBL_AVISOCANJEAR, "El cliente no tiene los puntos necesarios");
			}

			else if (estatus == "Desactivada")
			{
				SetDlgItemTextA(hDialogoActual, LBL_AVISOCANJEAR, "La promocion no esta activa");
			}

			else
			{
				int desc = stoi(descuento);
				int ventaAct = stoi(venta);
				float descuentoAct = desc * 0.01;

				float descuentofinal = ventaAct - (ventaAct * descuentoAct);
				string formatoVenta;
				formatoVenta = "A la compra de " + venta + "$" + " Se le aplicara un descuento del " + cDescuento + "% y la compra final seria: " + to_string(descuentofinal) + " Al Clientes " + nombreClienteGuardar;
				int respuesta = MessageBoxA(hDialogoActual, formatoVenta.c_str(), "Confirmacion Compra", MB_YESNO);
				if (respuesta == IDYES)
				{
					auxClientes->dineroGastado = auxClientes->dineroGastado + descuentofinal;
					auxClientes->puntos = auxClientes->puntos - puntosGuardados;
					auxP->canjeadasContador++;
					HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
					ShowWindow(hDlg, SW_SHOW);
					DestroyWindow(hDialogoActual);
				}
			}
		}
		break;

		case LBX_LISTCANJEPROMO:
		{
			switch (HIWORD(wParam))
			{//sw3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTCANJEPROMO, LB_GETCURSEL, NULL, NULL);
				promos* promosLista = (promos*)SendDlgItemMessage(hDialogoActual, LBX_LISTCANJEPROMO, LB_GETITEMDATA, indice, NULL);
				int num = promosLista->descuento * 100;
				string nums = to_string(num);
				
				SetDlgItemTextA(hDialogoActual, LBL_CANJENOMBREPROMO, promosLista->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CANJEPUNTOSPROMO, to_string(promosLista->puntosReq).c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CANJEDESCUENTOPROMO, nums.c_str());
				if (promosLista->estatus == 1)
				{
					SetDlgItemTextA(hDialogoActual, LBL_CANJEESTATUSPROMO, "Activa");
				}

				else
				{
					SetDlgItemTextA(hDialogoActual, LBL_CANJEESTATUSPROMO, "Desactivada");
				}

				SetDlgItemTextA(hDialogoActual, LBL_CANJEARPROMOID, to_string(promosLista->id).c_str());

			
			}
			break;

			}//sw3
		}
		break;

		case BTN_REGRESARCANJEPROMO:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_CANJEARELEGIRCLIENTE), NULL, fnDlgCanjear1);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

	

		}//SW2
	}
	break;

	}//sw1
	 
	return FALSE;
}

INT_PTR CALLBACK fnDlgCanjear1(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{

	char cnombreCliente[50];
	char cpuntosCliente[50];
	switch (uMensaje)
	{//sw1
	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_CANJEARNOMBREUS, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_CANJEAR);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);


		SetDlgItemTextA(hDialogoActual, LBL_CANJEARNOMBRECLIENTE, "");
		SetDlgItemTextA(hDialogoActual, LBL_PUNTOSCANJEAR, "");
		SetDlgItemTextA(hDialogoActual, LBL_CANJEARCLIENTEAVISO, "");


		auxClientes = inicioListaClientes;
		while (auxClientes != NULL)
		{
			string formato;
			formato = to_string(auxClientes->id) + " " + auxClientes->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTCLIENTESCANJEAR);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxClientes);
			auxClientes = auxClientes->sig;
		}

	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//SW2

		case BTN_SIG:
		{
			GetDlgItemTextA(hDialogoActual, LBL_CANJEARNOMBRECLIENTE, cnombreCliente, 50);
			string nombreCliente(cnombreCliente);
			GetDlgItemTextA(hDialogoActual, LBL_PUNTOSCANJEAR, cpuntosCliente, 50);
			string puntosCliente(cpuntosCliente);

			if (nombreCliente.empty() || puntosCliente.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_CANJEARCLIENTEAVISO, "Debe elegir un cliente");
			}

			else
			{
				nombreClienteGuardar = nombreCliente;
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_CANJEARPROMO), NULL, fnDlgCanjear2);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}
		}
		break;

		case LBX_LISTCLIENTESCANJEAR:
		{
			switch (HIWORD(wParam))
			{//SW3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTCLIENTESCANJEAR, LB_GETCURSEL, NULL, NULL);
				clientes* clientesLista = (clientes*)SendDlgItemMessage(hDialogoActual, LBX_LISTCLIENTESCANJEAR, LB_GETITEMDATA, indice, NULL);
				string num = to_string(clientesLista->puntos);
				
				SetDlgItemTextA(hDialogoActual, LBL_CANJEARNOMBRECLIENTE, clientesLista->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_PUNTOSCANJEAR, num.c_str());
			}

			}//SW3
		}
		break;

		case BTN_CANJEARREGRESA:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;
		
		}//SW2
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	}//sw1
	return FALSE;
}

//promo
void escribirBinPromos()
{
	auxP = inicioListaPromos;
	ofstream escribirPromos;
	escribirPromos.open("Promos.dat", ios::out | ios::binary);
	if (escribirPromos.is_open())
	{
		while (auxP != NULL)
		{
			escribirPromos.write((char*)auxP, sizeof(promos));
			auxP = auxP->sig;
		}
	}
	escribirPromos.close();
}
void leerBinPromos()
{
	fstream archivo;
	archivo.open("Promos.dat", ios::binary | ios::in | ios::ate); //at the end

	if (archivo.is_open())//es validar que el archivo exista y que haya sido abierto correctamente
	{
		int tamanoDeArchivo = archivo.tellg(); //tellg devuelve la posicion del cursor
		int totalDePromos = tamanoDeArchivo / sizeof(promos);

		for (int i = 0; i < totalDePromos; i++)
		{
			archivo.seekg(i * sizeof(promos)); // seekg establecemos la posicion del cursor

			promos* tempP = new promos;
			archivo.read((char*)tempP, sizeof(promos));
			tempP->sig = NULL;
			tempP->ant = NULL;

			if (inicioListaPromos == NULL)
			{
				inicioListaPromos = tempP;
				inicioListaPromos->ant = NULL;
				finListaPromos = tempP;
			}
			else
			{
				finListaPromos->sig = tempP;
				tempP->ant = finListaPromos;
				finListaPromos = tempP;

			}
		}
		int id = 1;
		auxP= inicioListaPromos;
		while (auxP != NULL)
		{
			auxP->id = id++;
			auxP = auxP->sig;
		}
	}
}

INT_PTR CALLBACK fnDlgPromoModificar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	string formato;

	switch (uMensaje)
	{//sw

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, IDC_STATIC12, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_PROMOMODIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, TXT_PMODNOMBRE, "");
		SetDlgItemTextA(hDialogoActual, TXT_PMODPUNTOS, "");
		SetDlgItemTextA(hDialogoActual, TXT_PMODDESCUENTO, "");
		SetDlgItemTextA(hDialogoActual, LBL_PMODESTATUS, "");
		SetDlgItemTextA(hDialogoActual, LBL_PMODERROR, "");
		SetDlgItemTextA(hDialogoActual, LBL_PMODID, "");

		auxP = inicioListaPromos;
		while (auxP != NULL)
		{
			string cont = to_string(auxP->id);
			formato = cont + "- " + auxP->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTCLIENTESMOSTRAR);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxP);
			auxP = auxP->sig;
		}

	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//sw2

		case BTN_PMODMODIFICAR:
		{
			int exitoNombre = 0;
			int nEstatus = 0;
			char cnombre[50], cpuntos[50], cdescuento[50], cestatus[50], cid[50];
			GetDlgItemTextA(hDialogoActual, TXT_PMODNOMBRE, cnombre, 50);
			string nombre(cnombre);
			GetDlgItemTextA(hDialogoActual, TXT_PMODPUNTOS, cpuntos, 50);
			string puntos(cpuntos);
			GetDlgItemTextA(hDialogoActual, TXT_PMODDESCUENTO, cdescuento, 50);
			string descuento(cdescuento);
			GetDlgItemTextA(hDialogoActual, LBL_PMODESTATUS, cestatus, 50);
			string estatus(cestatus);
			GetDlgItemTextA(hDialogoActual, LBL_PMODID, cid, 50);
			string id(cid);

			for (int i = 0; i < nombre.size(); i++)
			{
				if ((nombre[i] >= 65 && nombre[i] <= 90) || (nombre[i] >= 97 && nombre[i] <= 122) || nombre[i] == 32)
				{
					exitoNombre = 1;
				}

				else
				{
					exitoNombre = 0;
					break;
				}
			}



			if (nombre.empty() || puntos.empty() || descuento.empty() || estatus.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_PMODERROR, "Todos los campos son obligatorios");
			}

			else if (nombre.size() < 5 || nombre.size() > 50)
			{
				SetDlgItemTextA(hDialogoActual, LBL_PMODERROR, "El nombre minimo son 5 y maximo 50 caracteres");
			}

			else if (exitoNombre != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_PMODERROR, "El nombre solo admite letras y espacios");
			}

			else if (stoi(puntos) < 0)
			{
				SetDlgItemTextA(hDialogoActual, LBL_PMODERROR, "Los puntos no pueden ser negativos");
			}

			else if (stoi(descuento) <= 0 || stoi(descuento) >= 100)
			{
				SetDlgItemTextA(hDialogoActual, LBL_PMODERROR, "El descuento no puede ser menor o igual que  0 ni mayor o igual a 100");
			}

			else
			{
				if (estatus == "activa")
				{
					nEstatus = 1;
				}

				else if (estatus == "desactivada")
				{
					nEstatus = 0;
				}

				auxP = inicioListaPromos;
				while (auxP != NULL)
				{
					if (auxP->id == stoi(id))
					{
						break;
					}
					auxP = auxP->sig;
				}
				float num = stoi(descuento);
				num = num / 100;
				auxP->nombre = nombre;
				auxP->puntosReq = stoi(puntos);
				auxP->descuento = num;
				auxP->estatus = nEstatus;

				SetDlgItemTextA(hDialogoActual, TXT_PMODNOMBRE, "");
				SetDlgItemTextA(hDialogoActual, TXT_PMODPUNTOS, "");
				SetDlgItemTextA(hDialogoActual, TXT_PMODDESCUENTO, "");
				SetDlgItemTextA(hDialogoActual, LBL_PMODESTATUS, "");
				SetDlgItemTextA(hDialogoActual, LBL_PMODERROR, "Agregado exitosamente");
			}

		}
		break;

		case BTN_PMODACTIVAR:
		{
			SetDlgItemTextA(hDialogoActual, LBL_PMODESTATUS, "activa");
		}
		break;

		case BTN_PMODDESACTIVAR:
		{
			SetDlgItemTextA(hDialogoActual, LBL_PMODESTATUS, "desactivada");
		}
		break;

		case LBX_LISTPMOD:
		{
			switch (HIWORD(wParam))
			{//sw3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTPMOD, LB_GETCURSEL, NULL, NULL);
				promos* clientesListaPromos = (promos*)SendDlgItemMessage(hDialogoActual, LBX_LISTPMOD, LB_GETITEMDATA, indice, NULL);

				string puntos = to_string(clientesListaPromos->puntosReq);
				int num = clientesListaPromos->descuento * 100;
				string nums = to_string(num);
				string sid = to_string(clientesListaPromos->id);

				SetDlgItemTextA(hDialogoActual, TXT_PMODNOMBRE, clientesListaPromos->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, TXT_PMODPUNTOS, puntos.c_str());
				SetDlgItemTextA(hDialogoActual, TXT_PMODDESCUENTO, nums.c_str());

				SetDlgItemTextA(hDialogoActual, LBL_PMODID, sid.c_str());
				if (clientesListaPromos->estatus == 1)
				{
					SetDlgItemTextA(hDialogoActual, LBL_PMODESTATUS, "activa");
				}

				else if (clientesListaPromos->estatus == 0)
				{
					SetDlgItemTextA(hDialogoActual, LBL_PMODESTATUS, "desactivada");
				}


			}
			break;

			}//sw3
		}
		break;

		case BTN_PMODSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//sw2
	}
	break;

	}//sw

	return FALSE;
}
INT_PTR CALLBACK fnDlgPromoMostrar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	string formato;
	switch (uMensaje)
	{//sw

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, IDC_STATIC11, auxUs->nombre.c_str());
		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_PROMOMOSIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_PMOSNOMBRE, "");
		SetDlgItemTextA(hDialogoActual, LBL_PMOSPUNTOS, "");
		SetDlgItemTextA(hDialogoActual, LBL_PMOSDESCUENTO, "");
		SetDlgItemTextA(hDialogoActual, LBL_PMOSESTATUS, "");

		auxP = inicioListaPromos;
		while (auxP != NULL)
		{
			string cont = to_string(auxP->id);
			formato = cont + "- " + auxP->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTPMOS);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxP);
			auxP = auxP->sig;
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//sw

		case BTN_PMOSSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case LBX_LISTPMOS:
		{
			switch (HIWORD(wParam))
			{//SW3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTPMOS, LB_GETCURSEL, NULL, NULL);
				promos* clientesListaPromos = (promos*)SendDlgItemMessage(hDialogoActual, LBX_LISTPMOS, LB_GETITEMDATA, indice, NULL);

				string puntos = to_string(clientesListaPromos->puntosReq);
				int num = clientesListaPromos->descuento * 100;
				string nums = to_string(num) + "%";

				SetDlgItemTextA(hDialogoActual, LBL_PMOSNOMBRE, clientesListaPromos->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_PMOSPUNTOS, puntos.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_PMOSDESCUENTO, nums.c_str());
				if (clientesListaPromos->estatus == 1)
				{
					SetDlgItemTextA(hDialogoActual, LBL_PMOSESTATUS, "activa");
				}

				else if (clientesListaPromos->estatus == 0)
				{
					SetDlgItemTextA(hDialogoActual, LBL_PMOSESTATUS, "desactivada");
				}


			}
			break;

			}//SW3
		}
		break;

		}//sw
	}
	break;

	}//sw

	return FALSE;
}
INT_PTR CALLBACK fnDlgPromoAgregar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	switch (uMensaje)
	{//sw

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, IDC_STATIC0, auxUs->nombre.c_str());
		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_PROMOAGREGARIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_PAGREGARESTATUS, "");
		SetDlgItemTextA(hDialogoActual, LBL_PAGREGARERROR, "");

	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//sw2

		case BTN_PAGREGAR:
		{
			int exitoNombre = 0;
			int nEstatus = 0;
			char cnombre[50], cpuntos[50], cdescuento[50], cestatus[50];
			GetDlgItemTextA(hDialogoActual, TXT_PAGREGARNOMBRE, cnombre, 50);
			string nombre(cnombre);
			GetDlgItemTextA(hDialogoActual, TXT_PAGREGARPUNTOS, cpuntos, 50);
			string puntos(cpuntos);
			GetDlgItemTextA(hDialogoActual, TXT_PAGREGARDESCUENTO, cdescuento, 50);
			string descuento(cdescuento);
			GetDlgItemTextA(hDialogoActual, LBL_PAGREGARESTATUS, cestatus, 50);
			string estatus(cestatus);

			for (int i = 0; i < nombre.size(); i++)
			{
				if ((nombre[i] >= 65 && nombre[i] <= 90) || (nombre[i] >= 97 && nombre[i] <= 122) || nombre[i] == 32)
				{
					exitoNombre = 1;
				}

				else
				{
					exitoNombre = 0;
					break;
				}
			}



			if (nombre.empty() || puntos.empty() || descuento.empty() || estatus.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_PAGREGARERROR, "Todos los campos son obligatorios");
			}

			else if (nombre.size() < 5 || nombre.size() > 50)
			{
				SetDlgItemTextA(hDialogoActual, LBL_PAGREGARERROR, "El nombre minimo son 5 y maximo 50 caracteres");
			}

			else if (exitoNombre != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_PAGREGARERROR, "El nombre solo admite letras y espacios");
			}

			else if (stoi(puntos) < 0)
			{
				SetDlgItemTextA(hDialogoActual, LBL_PAGREGARERROR, "Los puntos no pueden ser negativos");
			}

			else if (stoi(descuento) <= 0 || stoi(descuento) >= 100)
			{
				SetDlgItemTextA(hDialogoActual, LBL_PAGREGARERROR, "El descuento no puede ser menor o igual que  0 ni mayor o igual a 100");
			}

			else
			{
				if (estatus == "activa")
				{
					nEstatus = 1;
				}

				else if (estatus == "desactivada")
				{
					nEstatus = 0;
				}

				agregarNodoPromos(nombre, stoi(puntos), stoi(descuento), nEstatus);
				SetDlgItemTextA(hDialogoActual, TXT_PAGREGARNOMBRE, "");
				SetDlgItemTextA(hDialogoActual, TXT_PAGREGARPUNTOS, "");
				SetDlgItemTextA(hDialogoActual, TXT_PAGREGARDESCUENTO, "");
				SetDlgItemTextA(hDialogoActual, LBL_PAGREGARESTATUS, "");
				SetDlgItemTextA(hDialogoActual, LBL_PAGREGARERROR, "Agregado exitosamente");
			}



		}
		break;

		case BTN_PAGREGARACTIVAR:
		{
			SetDlgItemTextA(hDialogoActual, LBL_PAGREGARESTATUS, "activa");
		}
		break;

		case BTN_PAGREGARDESACTIVAR:
		{
			SetDlgItemTextA(hDialogoActual, LBL_PAGREGARESTATUS, "desactivada");
		}
		break;

		case BTN_PAGREGARSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//sw2
	}

	}//sw

	return FALSE;
}
INT_PTR CALLBACK fnDlgPromoEliminar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	int eliminar = 0;
	string formato;

	switch (uMensaje)
	{//sw1

	case WM_INITDIALOG:
	{

		SetDlgItemTextA(hDialogoActual, IDC_STATIC8, auxUs->nombre.c_str());
		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_PROMOELIMINARIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);


		SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARNOMBRE, "");
		SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARAVISO, "");
		SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARDESCUENTO, "");
		SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARESTADO, "");
		SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARPUNTOS, "");
		SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARID, "");

		auxP = inicioListaPromos;
		while (auxP != NULL)
		{
			string cont = to_string(auxP->id);
			formato = cont + "- " + auxP->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTPROMOELIMINAR);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxP);
			auxP = auxP->sig;
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//SW2

		case BTN_PROMOELIMINAR:
		{

			char cId[50];
			GetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARID, cId, 50);
			string sId(cId);

			auxPEliminar = inicioListaPromos;
			while (auxPEliminar != NULL)
			{
				if (stoi(sId) == auxPEliminar->id)
				{
					eliminar = 1;
					break;
				}
				auxPEliminar = auxPEliminar->sig;
			}


			if (eliminar == 1)
			{

				if (auxPEliminar == NULL)
				{
					SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARAVISO, "Necesita Seleccionar una Promocion");
				}

				else if (auxPEliminar == inicioListaPromos)
				{
					inicioListaPromos = inicioListaPromos->sig;
					if (inicioListaPromos != NULL)
					{
						inicioListaPromos->ant = NULL;
					}
					else
					{
						finListaPromos = NULL;
					}
					auxPEliminar = NULL;
					delete auxPEliminar;
				}

				else if (auxPEliminar == finListaPromos)
				{
					finListaPromos = finListaPromos->ant;
					if (finListaPromos != NULL)
					{
						finListaPromos->sig = NULL;
					}
					else {
						inicioListaPromos = NULL;
					}
					auxPEliminar = NULL;
					delete auxPEliminar;
				}

				else
				{
					auxPEliminar->ant->sig = auxPEliminar->sig;
					auxPEliminar->sig->ant = auxPEliminar->ant;
					auxPEliminar = NULL;
					delete auxPEliminar;
				}


				int id = 1;
				auxP = inicioListaPromos;
				while (auxP != NULL)
				{
					auxP->id = id++;
					auxP = auxP->sig;
				}
				SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARAVISO, "Promocion Eliminada");
			}

			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARAVISO, "Necesita Seleccionar una Promocion");
			}

		}
		break;

		case BTN_PROMOELIMINARSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case LBX_LISTPROMOELIMINAR:
		{
			switch (HIWORD(wParam))
			{//sw3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTPROMOELIMINAR, LB_GETCURSEL, NULL, NULL);
				promos* promosListaEliminar = (promos*)SendDlgItemMessage(hDialogoActual, LBX_LISTPROMOELIMINAR, LB_GETITEMDATA, indice, NULL);
				int num = promosListaEliminar->descuento * 100;
				string nums = to_string(num) + "%";
				string puntos = to_string(promosListaEliminar->puntosReq);
				string descuento = to_string(promosListaEliminar->descuento);
				string id = to_string(promosListaEliminar->id);
				SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARNOMBRE, promosListaEliminar->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARPUNTOS, puntos.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARDESCUENTO, nums.c_str());
				if (promosListaEliminar->estatus == 0)
				{
					SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARESTADO, "Desactivada");
				}

				else if (promosListaEliminar->estatus == 1)
				{
					SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARESTADO, "Activada");
				}

				SetDlgItemTextA(hDialogoActual, LBL_PROMOELIMINARID, id.c_str());
			}
			break;

			}//sw3
			break;

		}
		break;

		}//SW2
	}
	break;

	}//sw1
	return FALSE;
}
//promo


//clientes
void escribirBinClientes()
{
	auxClientes = inicioListaClientes;
	ofstream escribirCliente;
	escribirCliente.open("Clientes.dat", ios::out | ios::binary);
	if (escribirCliente.is_open())
	{
		while (auxClientes != NULL)
		{
			escribirCliente.write((char*)auxClientes, sizeof(clientes));
			auxClientes = auxClientes->sig;
		}
	}
	escribirCliente.close();
}
void leerBinClientes()
{
	fstream archivo;
	archivo.open("Clientes.dat", ios::binary | ios::in | ios::ate); //at the end

	if (archivo.is_open())//es validar que el archivo exista y que haya sido abierto correctamente
	{
		int tamanoDeArchivo = archivo.tellg(); //tellg devuelve la posicion del cursor
		int totalDeClientes = tamanoDeArchivo / sizeof(clientes);

		for (int i = 0; i < totalDeClientes; i++)
		{
			archivo.seekg(i * sizeof(clientes)); // seekg establecemos la posicion del cursor

			clientes* tempC = new clientes;
			archivo.read((char*)tempC, sizeof(clientes));
			tempC->sig = NULL;
			tempC->ant = NULL;

			if (inicioListaClientes == NULL)
			{
				inicioListaClientes = tempC;
				inicioListaClientes->ant = NULL;
				finListaClientes = tempC;
			}
			else
			{
				finListaClientes->sig = tempC;
				tempC->ant = finListaClientes;
				finListaClientes = tempC;

			}
		}
		int id = 1;
		auxClientes = inicioListaClientes;
		while (auxClientes != NULL)
		{
			auxClientes->id = id++;
			auxClientes = auxClientes->sig;
		}
	}
}

INT_PTR CALLBACK fnDlgClientesEliminar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	int eliminar = 0;
	int id = 0;
	int iPuntos = 0;
	string formato;
	switch (uMensaje)
	{//sw1

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARUSER, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_CLIENTESELIMINARIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		int id = 1;
		auxClientes = inicioListaClientes;
		while (auxClientes != NULL)
		{
			auxClientes->id = id++;
			auxClientes = auxClientes->sig;
		}

		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARNOMBRE, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARCORREO, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARFECHA, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARSUCURSAL, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARID, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARAVISO, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARPUNTOS, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARUSER, auxUs->nombre.c_str());

		auxClientes = inicioListaClientes;
		while (auxClientes != NULL)
		{
			string cont = to_string(auxClientes->id);
			formato = cont + "- " + auxClientes->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTCLIENTESELIMINAR);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxClientes);
			auxClientes = auxClientes->sig;
		}
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//sw2

		case BTN_CLIENTESELIMINAR:
		{
			char cId[50];
			GetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARID, cId, 50);
			string sId(cId);

			auxClientesEliminar = inicioListaClientes;
			while (auxClientesEliminar != NULL)
			{
				if (stoi(sId) == auxClientesEliminar->id)
				{
					eliminar = 1;
					break;
				}
				auxClientesEliminar = auxClientesEliminar->sig;
			}


			if (eliminar == 1)
			{

				if (auxClientesEliminar == NULL)
				{
					SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARAVISO, "Necesita Seleccionar un Clientes");
				}

				else if (auxClientesEliminar == inicioListaClientes)
				{
					inicioListaClientes = inicioListaClientes->sig;
					if (inicioListaClientes != NULL)
					{
						inicioListaClientes->ant = NULL;
					}
					else
					{
						finListaClientes = NULL;
					}
					auxClientesEliminar = NULL;
					delete auxClientesEliminar;
				}

				else if (auxClientesEliminar == finListaClientes)
				{
					finListaClientes = finListaClientes->ant;
					if (finListaClientes != NULL)
					{
						finListaClientes->sig = NULL;
					}
					else {
						inicioListaClientes = NULL;
					}
					auxClientesEliminar = NULL;
					delete auxClientesEliminar;
				}

				else
				{
					auxClientesEliminar->ant->sig = auxClientesEliminar->sig;
					auxClientesEliminar->sig->ant = auxClientesEliminar->ant;
					auxClientesEliminar = NULL;
					delete auxClientesEliminar;
				}
				

				int id = 1;
				auxClientes = inicioListaClientes;
				while (auxClientes != NULL)
				{
					auxClientes->id = id++;
					auxClientes = auxClientes->sig;
				}
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARAVISO, "Cliente Eliminado");
			}

			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARAVISO, "Necesita Seleccionar un Clientes");
			}
		}
		break;

		case LBX_LISTCLIENTESELIMINAR:
		{
			switch (HIWORD(wParam))
			{//sw3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTCLIENTESELIMINAR, LB_GETCURSEL, NULL, NULL);
				clientes* clientesListaEliminar = (clientes*)SendDlgItemMessage(hDialogoActual, LBX_LISTCLIENTESELIMINAR, LB_GETITEMDATA, indice, NULL);
				iPuntos = clientesListaEliminar->puntos;
				id = clientesListaEliminar->id;
				string sId = to_string(id);
				string sPuntos = to_string(iPuntos);
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARNOMBRE, clientesListaEliminar->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARCORREO, clientesListaEliminar->correo.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARSUCURSAL, clientesListaEliminar->sucursal.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARFECHA, clientesListaEliminar->fecha.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARPUNTOS, sPuntos.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESELIMINARID, sId.c_str());
			}
			break;

			}//sw3
		}
		break;

		case BTN_CLIENTESELIMINARSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//sw2

	}
	break;

	}//sw1
	return FALSE;
}
INT_PTR CALLBACK fnDlgClientesModificar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	int exitoEmail1 = 0;
	int exitoEmail2 = 0;
	int exitoNombre = 0;
	int exitoEmail3 = 0;
	int iPuntos = 0;
	int id = 0;
	string formato;
	switch (uMensaje)
	{//sw

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODUS, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_CLIENTESMODIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		int id = 1;
		auxClientes = inicioListaClientes;
		while (auxClientes != NULL)
		{
			auxClientes->id = id++;
			auxClientes = auxClientes->sig;
		}

		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODSUCURSAL, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODFECHA, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODPUNTOS, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODERROR, "");

		auxClientes = inicioListaClientes;
		while (auxClientes != NULL)
		{
			string cont = to_string(auxClientes->id);
			formato = cont + "- " + auxClientes->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTCLIENTESMOD);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxClientes);
			auxClientes = auxClientes->sig;
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{

		switch (LOWORD(wParam))
		{//sw2

		case BTN_CLIENTEMODIFICAR:
		{
			char cnombre[50], ccorreo[50], cid[50];
			GetDlgItemTextA(hDialogoActual, TXT_CLIENTESMODNOMBRE, cnombre, 50);
			string nombre(cnombre);
			GetDlgItemTextA(hDialogoActual, TXT_CLIENTESMODCORREO, ccorreo, 50);
			string correo(ccorreo);
			GetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODID, cid, 50);
			string id(cid);

			for (int i = 0; i < nombre.size(); i++)
			{
				if ((nombre[i] >= 65 && nombre[i] <= 90) || (nombre[i] >= 97 && nombre[i] <= 122) || nombre[i] == 32)
				{
					exitoNombre = 1;
				}

				else
				{
					exitoNombre = 0;
					break;
				}
			}

			for (int i = 0; i < correo.size(); i++)
			{
				if (correo[i] == 64)
				{
					exitoEmail1 = 1;
				}

				if (correo[i] == 46)
				{
					exitoEmail2 = 1;

				}

				if (correo[i] == 32)
				{
					exitoEmail3 = 1;
				}
			}

			if (nombre.empty() || correo.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODERROR, "Todos Los campos son Obligatorios");
			}

			else if (nombre.size() < 5 || nombre.size() > 50)
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODERROR, "El nombre debe tener 5 caracteres minimo y 50 maximo");
			}

			else if (correo.size() < 5 || correo.size() > 25)
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODERROR, "El email debe tener 5 caracteres minimo y 50 maximo");
			}

			else if (exitoNombre != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODERROR, "Solo puede tener letras y espacios");
			}

			else if (exitoEmail1 == 1 || exitoEmail2 == 1 || exitoEmail3 == 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODERROR, "no puede tener @, espacio o .");
			}

			else
			{
				auxClientes = inicioListaClientes;
				while (auxClientes != NULL)
				{
					if (auxClientes->id == stoi(id))
					{
						auxClientes->nombre = nombre;
						auxClientes->correo = correo;
						break;
					}
					auxClientes = auxClientes->sig;
				}
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODERROR, "Cliente Modificado exitoso");
				SetDlgItemTextA(hDialogoActual, TXT_CLIENTESMODNOMBRE, "");
				SetDlgItemTextA(hDialogoActual, TXT_CLIENTESMODCORREO, "");
			}
		}
		break;

		case LBX_LISTCLIENTESMOD:
		{
			switch (HIWORD(wParam))
			{//sw3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTCLIENTESMOD, LB_GETCURSEL, NULL, NULL);
				clientes* clientesListaModificar = (clientes*)SendDlgItemMessage(hDialogoActual, LBX_LISTCLIENTESMOD, LB_GETITEMDATA, indice, NULL);
				iPuntos = clientesListaModificar->puntos;
				id = clientesListaModificar->id;
				string sId = to_string(id);
				string sPuntos = to_string(iPuntos);
				SetDlgItemTextA(hDialogoActual, TXT_CLIENTESMODNOMBRE, clientesListaModificar->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, TXT_CLIENTESMODCORREO, clientesListaModificar->correo.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODSUCURSAL, clientesListaModificar->sucursal.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODFECHA, clientesListaModificar->fecha.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODPUNTOS, sPuntos.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMODID, sId.c_str());
			}
			break;

			}//sw3
		}
		break;


		case BTN_CLIENTESMODIFICARSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//sw2
	}
	break;

	}//sw
	return FALSE;
}
INT_PTR CALLBACK fnDlgClientesMostrar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	string formato;
	switch (uMensaje)
	{//sw

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRARUS, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_CLIENTESMOSIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRARNOMBRE, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRAREMAIL, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRARSUCURSAL, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRARFECHA, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRARPUNTOS, "");

		int id = 1;
		auxClientes = inicioListaClientes;
		while (auxClientes != NULL)
		{
			auxClientes->id = id++;
			auxClientes = auxClientes->sig;
		}

		auxClientes = inicioListaClientes;

		while (auxClientes != NULL)
		{
			string cont = to_string(auxClientes->id);
			formato = cont + "- " + auxClientes->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTCLIENTESMOSTRAR);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxClientes);
			auxClientes = auxClientes->sig;
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//sw2

		case LBX_LISTCLIENTESMOSTRAR:
		{
			switch (HIWORD(wParam))
			{//sw3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTCLIENTESMOSTRAR, LB_GETCURSEL, NULL, NULL);
				clientes* clientesListaMostrar = (clientes*)SendDlgItemMessage(hDialogoActual, LBX_LISTCLIENTESMOSTRAR, LB_GETITEMDATA, indice, NULL);
				int puntos = clientesListaMostrar->puntos;
				string sPuntos = to_string(puntos);
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRARNOMBRE, clientesListaMostrar->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRAREMAIL, clientesListaMostrar->correo.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRARSUCURSAL, clientesListaMostrar->sucursal.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRARFECHA, clientesListaMostrar->fecha.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESMOSTRARPUNTOS, sPuntos.c_str());
			}
			break;

			}//sw3
		}
		break;

		case BTN_CLIENTESMOSTRARSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//sw2
	}
	break;

	}//sw
	return FALSE;
}
INT_PTR CALLBACK fnDlgClientesAgregar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	int exitoEmail1 = 0;
	int exitoEmail2 = 0;
	int exitoNombre = 0;
	int exitoEmail3 = 0;

	switch (uMensaje)
	{//sw

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESUS, auxUs->nombre.c_str());


		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_CLIENTESAGREGARIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARFECHA, formatoFechaActual.c_str());
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARSUCURSAL, auxUs->sucursal.c_str());
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARERROR, "");
		SetDlgItemTextA(hDialogoActual, LBL_CLIENTESUS, auxUs->nombre.c_str());
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//sw2

		case BTN_CLIENTESAGREGAR:
		{
			char cnombre[50], cemail[50], csucursal[50], cfecha[50];
			GetDlgItemTextA(hDialogoActual, TXT_CLIENTESAGREGARNOMBRE, cnombre, 50);
			string nombre(cnombre);
			GetDlgItemTextA(hDialogoActual, TXT_CLIENTESAGREGAREMAIL, cemail, 50);
			string email(cemail);
			GetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARSUCURSAL, csucursal, 50);
			string sucursal(csucursal);
			GetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARFECHA, cfecha, 50);
			string fecha(cfecha);

			for (int i = 0; i < nombre.size(); i++)
			{
				if ((nombre[i] >= 65 && nombre[i] <= 90) || (nombre[i] >= 97 && nombre[i] <= 122) || nombre[i] == 32)
				{
					exitoNombre = 1;
				}

				else
				{
					exitoNombre = 0;
					break;
				}
			}

			for (int i = 0; i < email.size(); i++)
			{
				if (email[i] == 64)
				{
					exitoEmail1 = 1;
				}

				if (email[i] == 46)
				{
					exitoEmail2 = 1;

				}

				if (email[i] == 32)
				{
					exitoEmail3 = 1;
				}
			}

			if (nombre.empty() || email.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARERROR, "Todos Los campos son Obligatorios");
			}

			else if (nombre.size() < 5 || nombre.size() > 50)
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARERROR, "El nombre debe tener 5 caracteres minimo y 50 maximo");
			}

			else if (email.size() < 5 || email.size() > 25)
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARERROR, "El email debe tener 5 caracteres minimo y 50 maximo");
			}

			else if (exitoNombre != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARERROR, "Solo puede tener letras y espacios");
			}

			else if (exitoEmail1 == 1 || exitoEmail2 == 1 || exitoEmail3 == 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARERROR, "no puede incluir espacio, @ o .");
			}

			else
			{
				agregarNodoClientes(nombre, email, sucursal, fecha);
				SetDlgItemTextA(hDialogoActual, LBL_CLIENTESAGREGARERROR, "Cliente agregado exitoso");
				SetDlgItemTextA(hDialogoActual, TXT_CLIENTESAGREGARNOMBRE, "");
				SetDlgItemTextA(hDialogoActual, TXT_CLIENTESAGREGAREMAIL, "");
			}
		}
		break;

		case BTN_CLIENTESAGREGARSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//sw2
	}
	break;

	}//sw

	return FALSE;
}
//clientes


//sucursales
void escribirBinSucursales()
{
	auxSu = inicioListaSucursal;
	ofstream escribirSucursales;
	escribirSucursales.open("Sucursales.dat", ios::out | ios::binary);
	if (escribirSucursales.is_open())
	{
		while (auxSu != NULL)
		{
			escribirSucursales.write((char*)auxSu, sizeof(sucursales));
			auxSu = auxSu->sig;
		}
	}
	escribirSucursales.close();
}
void leerBinSucursales()
{
	fstream archivo;
	archivo.open("Sucursales.dat", ios::binary | ios::in | ios::ate); //at the end

	if (archivo.is_open())//es validar que el archivo exista y que haya sido abierto correctamente
	{
		int tamanoDeArchivo = archivo.tellg(); //tellg devuelve la posicion del cursor
		int totalDeSucursales = tamanoDeArchivo / sizeof(sucursales);

		for (int i = 0; i < totalDeSucursales; i++)
		{
			archivo.seekg(i * sizeof(sucursales)); // seekg establecemos la posicion del cursor

			sucursales* tempS = new sucursales;
			archivo.read((char*)tempS, sizeof(sucursales));
			tempS->sig = NULL;
			tempS->ant = NULL;

			if (inicioListaSucursal == NULL)
			{
				inicioListaSucursal = tempS;
				inicioListaSucursal->ant = NULL;
				finListaSucursal = tempS;
			}
			else
			{
				finListaSucursal->sig = tempS;
				tempS->ant = finListaSucursal;
				finListaSucursal = tempS;

			}
		}
		int id = 1;
		auxSu = inicioListaSucursal;
		while (auxSu != NULL)
		{
			auxSu->id = id++;
			auxSu = auxSu->sig;
		}
	}
}

INT_PTR CALLBACK fnDlgSucursalModificar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{

	string formato;
	switch (uMensaje)
	{//sw
	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, IDC_STATIC6, auxUs->nombre.c_str());


		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_SUCURSALMODIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_SUCURSALMODID, "");
		SetDlgItemTextA(hDialogoActual, LBL_ERRORMODSUC, "");

		auxSu = inicioListaSucursal;
		while (auxSu != NULL)
		{
			string si = to_string(auxSu->id);
			formato = si + "-" + auxSu->nombre + " " + auxSu->direccion;
			HWND hListBoxS = GetDlgItem(hDialogoActual, LBX_LISTSUCURSALMOD);
			int indice = SendMessageA(hListBoxS, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBoxS, LB_SETITEMDATA, indice, (LPARAM)auxSu);
			auxSu = auxSu->sig;
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//sw2
		case LBX_LISTSUCURSALMOD:
		{
			switch (HIWORD(wParam))
			{//sw3
			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTSUCURSALMOD, LB_GETCURSEL, NULL, NULL);
				sucursales* sucursalLista = (sucursales*)SendDlgItemMessage(hDialogoActual, LBX_LISTSUCURSALMOD, LB_GETITEMDATA, indice, NULL);

				string idsu = to_string(sucursalLista->id);


				SetDlgItemTextA(hDialogoActual, TXT_SUCURSALMODNOMBRE, sucursalLista->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, TXT_SUCURSALMODDIRECCION, sucursalLista->direccion.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_SUCURSALMODID, idsu.c_str());
			}
			break;

			}//sw3
		}
		break;
		case BTN_SUCURSALMOD:
		{
			char nombre[50], direccion[50], id[3];
			int exitoNombreSucursal = 0;
			GetDlgItemTextA(hDialogoActual, TXT_SUCURSALMODNOMBRE, nombre, 50);
			string snombre(nombre);
			GetDlgItemTextA(hDialogoActual, TXT_SUCURSALMODDIRECCION, direccion, 50);
			string sdireccion(direccion);
			GetDlgItemTextA(hDialogoActual, LBL_SUCURSALMODID, id, 3);
			string sid(id);


			for (int i = 0; i < snombre.size(); i++)
			{
				if ((snombre[i] >= 65 && snombre[i] <= 90) || (snombre[i] >= 97 && snombre[i] <= 122) || snombre[i] == 32)
				{
					exitoNombreSucursal = 1;
				}
				else
				{
					exitoNombreSucursal = 0;
					break;
				}
			}

			if (snombre.empty() || sdireccion.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODSUC, "Todos Los campos son obligatorios");
			}

			else if (snombre.size() <= 5 || snombre.size() >= 50)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODSUC, "El nombre requiere minimo 5 y maximo 50 caracteres");
			}

			else if (exitoNombreSucursal != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODSUC, "Solo se permiten  letras y espacios");
			}

			else if (auxUs->sucursal == snombre)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODSUC, "No puede modoficar la sucursal actual");
			}

			else if (auxUs->sucursal != snombre) {
				int nid = stoi(sid);
				auxSu = inicioListaSucursal;
				while (auxSu != NULL)
				{
					if (auxSu->id == nid)
					{///// no jala direccion CAMBIAR

						auxSu->nombre = snombre;
						auxSu->direccion = sdireccion;
					}
					auxSu = auxSu->sig;
				}
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODSUC, "Sucursal Modificada con exito");
				SetDlgItemTextA(hDialogoActual, TXT_SUCURSALMODNOMBRE, "");
				SetDlgItemTextA(hDialogoActual, TXT_SUCURSALMODDIRECCION, "");
			}


		}
		break;

		case BTN_SALIRSUCMOD:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//sw2

	}
	break;
	}//sw

	return FALSE;
}
INT_PTR CALLBACK fnDlgSucursalMostar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	string formato;
	switch (uMensaje)
	{//sw1

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, IDC_STATIC5, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_SUCURSALESMOSTRARIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_SUCURSALMOSTRARNOMBRE, "");
		SetDlgItemTextA(hDialogoActual, LBL_SUCURSALMOSDIRECCION, "");

		auxSu = inicioListaSucursal;
		while (auxSu != NULL)
		{
			string si = to_string(auxSu->id);
			formato = si + "-" + auxSu->nombre + " " + auxSu->direccion;
			HWND hListBoxS = GetDlgItem(hDialogoActual, LBX_LISTSUCURSALESMOS);
			int indice = SendMessageA(hListBoxS, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBoxS, LB_SETITEMDATA, indice, (LPARAM)auxSu);
			auxSu = auxSu->sig;
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//sw2

		case LBX_LISTSUCURSALESMOS:
		{
			switch (HIWORD(wParam))
			{//sw3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTSUCURSALESMOS, LB_GETCURSEL, NULL, NULL);
				sucursales* sucursalLista = (sucursales*)SendDlgItemMessage(hDialogoActual, LBX_LISTSUCURSALESMOS, LB_GETITEMDATA, indice, NULL);

				SetDlgItemTextA(hDialogoActual, LBL_SUCURSALMOSTRARNOMBRE, sucursalLista->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_SUCURSALMOSDIRECCION, sucursalLista->direccion.c_str());
			}
			break;

			}//sw3
		}
		break;


		case BTN_SALIRMOSSUCU:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//sw2

	}
	break;

	}//sw1
	return FALSE;
}
INT_PTR CALLBACK fnDlgSucursalAgregar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	switch (uMensaje)
	{//sw1

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, IDC_STATIC4, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_SUCURSALESIMGAGREGAR);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);
		SetDlgItemTextA(hDialogoActual, LBL_SUCURSALAGREGARERROR, "");
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//sw2

		case BTN_AGREGARSUCURSAL:
		{
			char nombre[50], direccion[50];
			int exitoNombreSucursal = 0;
			GetDlgItemTextA(hDialogoActual, TXT_SUCURSALNOMBRE, nombre, 50);
			string snombre(nombre);
			GetDlgItemTextA(hDialogoActual, TXT_SUCURSALDIRECCION, direccion, 50);
			string sdireccion(direccion);

			for (int i = 0; i < snombre.size(); i++)
			{
				if ((snombre[i] >= 65 && snombre[i] <= 90) || (snombre[i] >= 97 && snombre[i] <= 122) || snombre[i] == 32)
				{
					exitoNombreSucursal = 1;
				}

				else
				{
					exitoNombreSucursal = 0;
					break;
				}
			}

			if (snombre.empty() || sdireccion.empty() || snombre.size() <= 5 || snombre.size() >= 50 || exitoNombreSucursal != 1)
			{
				if (snombre.empty() || sdireccion.empty())
				{
					SetDlgItemTextA(hDialogoActual, LBL_SUCURSALAGREGARERROR, "Todos Los campos son obligatorios");
				}

				if (snombre.size() <= 5 || snombre.size() >= 50)
				{
					SetDlgItemTextA(hDialogoActual, LBL_SUCURSALAGREGARERROR, "El nombre requiere minimo 5 y maximo 50 caracteres");
				}

				if (exitoNombreSucursal != 1)
				{
					SetDlgItemTextA(hDialogoActual, LBL_SUCURSALAGREGARERROR, "Solo se permiten  letras y espacios");
				}

			}

			else
			{
				agregarNodoSucursal(snombre, sdireccion);

				SetDlgItemTextA(hDialogoActual, TXT_SUCURSALNOMBRE, "");
				SetDlgItemTextA(hDialogoActual, TXT_SUCURSALDIRECCION, "");
				SetDlgItemTextA(hDialogoActual, LBL_SUCURSALAGREGARERROR, "Sucursal agregada con exito");
			}

		}
		break;

		case BTN_SUCURSALAGREGARSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//sw2
	}
	break;

	}//sw1
	return FALSE;
}
INT_PTR CALLBACK fnDlgSucursalEliminar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	string nId;
	int eliminar = 0;
	string formato;
	switch (uMensaje)
	{//sw1

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, IDC_STATIC3, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_SUCURSALIMGELIMINAR);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARNOMBRE, "");
		SetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARDIRECCION, "");
		SetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARAVISO, "");
		SetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARID, "");

		auxSu = inicioListaSucursal;
		while (auxSu != NULL)
		{
			string si = to_string(auxSu->id);
			formato = si + "-" + auxSu->nombre + " " + auxSu->direccion;
			HWND hListBoxS = GetDlgItem(hDialogoActual, LBX_LISTSUCURSALELIMINAR);
			int indice = SendMessageA(hListBoxS, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBoxS, LB_SETITEMDATA, indice, (LPARAM)auxSu);
			auxSu = auxSu->sig;
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//SW2

		case LBX_LISTSUCURSALELIMINAR:
		{
			switch (HIWORD(wParam))
			{//SW3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTSUCURSALELIMINAR, LB_GETCURSEL, NULL, NULL);
				sucursales* sucursalLista = (sucursales*)SendDlgItemMessage(hDialogoActual, LBX_LISTSUCURSALELIMINAR, LB_GETITEMDATA, indice, NULL);

				nId = to_string(sucursalLista->id);

				SetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARNOMBRE, sucursalLista->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARDIRECCION, sucursalLista->direccion.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARID, nId.c_str());
			}
			break;

			}//SW3
		}
		break;

		case BTN_SUCURSALELIMINAR:
		{

			char cId[3];
			GetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARID, cId, 3);
			string id(cId);
			auxSuEliminar = inicioListaSucursal;

			while (auxSuEliminar != NULL)
			{
				if (stoi(id) == auxSuEliminar->id) {
					eliminar = 1;
					break;
				}
				auxSuEliminar = auxSuEliminar->sig;
			}


			if (eliminar == 1)
			{

				if (auxSuEliminar == NULL)
				{
					SetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARAVISO, "Necesita Seleccionar una Sucursal");
				}

				else if (auxSuEliminar == inicioListaSucursal)
				{
					inicioListaSucursal = inicioListaSucursal->sig;
					if (inicioListaSucursal != NULL) {
						inicioListaSucursal->ant = NULL;
					}
					else
					{
						finListaSucursal = NULL;
					}
					auxSuEliminar = NULL;
					delete auxSuEliminar;
				}

				else if (auxSuEliminar == finListaSucursal)
				{
					finListaSucursal = finListaSucursal->ant;
					if (finListaSucursal != NULL)
					{
						finListaSucursal->sig = NULL;
					}
					else {
						inicioListaSucursal = NULL;
					}
					auxSuEliminar = NULL;
					delete auxSuEliminar;
				}

				else
				{
					auxSuEliminar->ant->sig = auxSuEliminar->sig;
					auxSuEliminar->sig->ant = auxSuEliminar->ant;
					auxSuEliminar = NULL;
					delete auxSuEliminar;
				}

				int id = 1;
				auxSu = inicioListaSucursal;
				while (auxSu != NULL)
				{
					auxSu->id = id++;
					auxSu = auxSu->sig;
				}
				SetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARAVISO, "Sucursal Eliminada");
			}

			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_SUCURSALELIMINARAVISO, "Necesita Seleccionar una Sucursal");
			}
		
		}
		break;
		
		case BTN_SUCURSALELIMINARSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//SW2
	}
	break;

	}//sw1

	return FALSE;
}

//sucursales


//usuarios ventanas
void escribirBinUsuario()
{
	auxUsM = inicioListaUser;
	ofstream escribirUser;
	escribirUser.open("Usuarios.dat", ios::out | ios::binary);
	if (escribirUser.is_open())
	{
		while (auxUsM != NULL)
		{
			escribirUser.write((char*)auxUsM, sizeof(usuarios));
			auxUsM = auxUsM->sig;
		}
	}
	escribirUser.close();
}
void leerBinUsuario()
{

	fstream archivo;
	archivo.open("Usuarios.dat", ios::binary | ios::in | ios::ate); //at the end

	if (archivo.is_open())//es validar que el archivo exista y que haya sido abierto correctamente
	{
		int tamanoDeArchivo = archivo.tellg(); //tellg devuelve la posicion del cursor
		int totalDeUsuarios = tamanoDeArchivo / sizeof(usuarios);

		for (int i = 0; i < totalDeUsuarios; i++)
		{
			archivo.seekg(i * sizeof(usuarios)); // seekg establecemos la posicion del cursor

			usuarios* temp = new usuarios;
			archivo.read((char*)temp, sizeof(usuarios));
			temp->sig = NULL;
			temp->ant = NULL;

			if (inicioListaUser == NULL)
			{
				inicioListaUser = temp;
				inicioListaUser->ant = NULL;
				finListaUser = temp;
			}
			else
			{
				finListaUser->sig = temp;
				temp->ant = finListaUser;
				finListaUser = temp;

			}
		}
	}
	archivo.close();
	
	int id = 1;
	auxUsM = inicioListaUser;
	while (auxUsM != NULL)
	{
		auxUsM->id = id++;
		auxUsM = auxUsM->sig;
	}
}

INT_PTR CALLBACK fnDlgUsuarioEliminar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	int eliminar = 0;
	int contador = 1;
	string formato;
	switch (uMensaje)
	{// inicio sw

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_INITDIALOG:
	{

		SetDlgItemTextA(hDialogoActual, IDC_STATIC2, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_USUARIOELIMINARIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_USERNOMBELIMINAR, "");
		SetDlgItemTextA(hDialogoActual, LBL_USERUSUARIOELIMINAR, "");
		SetDlgItemTextA(hDialogoActual, LBL_USERPASSWORDELIMINAR, "");
		SetDlgItemTextA(hDialogoActual, LBL_USERTIPOELIMINAR, "");
		SetDlgItemTextA(hDialogoActual, LBL_USERSUCURSALELIMINAR, "");
		SetDlgItemTextA(hDialogoActual, LBL_ELIMINARAVISO, "");
		auxUsM = inicioListaUser;
		while (auxUsM != NULL)
		{
			string scontador = to_string(contador);
			formato = scontador + "- " + auxUsM->nombre;
			HWND hListBoxE = GetDlgItem(hDialogoActual, LBX_LISTUSUARIOSELIMINAR);
			int indice = SendMessageA(hListBoxE, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBoxE, LB_SETITEMDATA, indice, (LPARAM)auxUsM);
			contador++;
			auxUsM = auxUsM->sig;

		}
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//inicio sw2

		case BTN_SALIRELIMINARUSER:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;


		case BTN_USUARIOSELIMINAR:
		{
			char nombre[50];
			GetDlgItemTextA(hDialogoActual, LBL_USERNOMBELIMINAR, nombre, 50);
			string snombre(nombre);

			auxEliminar = inicioListaUser;

			while (auxEliminar != NULL)
			{
				if (snombre == auxEliminar->nombre) {
					eliminar = 1;
					break;
				}
				auxEliminar = auxEliminar->sig;
			}

			if (snombre == auxUs->nombre)
			{
				eliminar = 0;
				SetDlgItemTextA(hDialogoActual, LBL_ELIMINARAVISO, "No se puede eliminar usuario actual");
			}

			if (eliminar == 1)
			{
				auxEliminar = inicioListaUser;
				while (auxEliminar != NULL && auxEliminar->nombre != snombre) {
					auxEliminar = auxEliminar->sig;
				}

				if (auxEliminar == NULL)
				{
					SetDlgItemTextA(hDialogoActual, LBL_ELIMINARAVISO, "Necesita Seleccionar un Usuario");
				}

				else if (auxEliminar == inicioListaUser)
				{
					inicioListaUser = inicioListaUser->sig;
					if (inicioListaUser != NULL) {
						inicioListaUser->ant = NULL;
					}
					else
					{
						finListaUser = NULL;
					}
					auxEliminar = NULL;
					delete auxEliminar;
				}

				else if (auxEliminar == finListaUser)
				{
					finListaUser = finListaUser->ant;
					if (finListaUser != NULL)
					{
						finListaUser->sig = NULL;
					}
					else {
						inicioListaUser = NULL;
					}
					auxEliminar = NULL;
					delete auxEliminar;
				}

				else
				{
					auxEliminar->ant->sig = auxEliminar->sig;
					auxEliminar->sig->ant = auxEliminar->ant;
					auxEliminar = NULL;
					delete auxEliminar;
				}

				int id = 1;
				auxUsM = inicioListaUser;
				while (auxUsM != NULL)
				{
					auxUsM->id = id++;
					auxUsM = auxUsM->sig;
				}
				SetDlgItemTextA(hDialogoActual, LBL_ELIMINARAVISO, "Usuario Eliminado");
			}

			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ELIMINARAVISO, "Necesita Seleccionar un Usuario");
			}
		}
		break;

		case LBX_LISTUSUARIOSELIMINAR:
		{
			switch (HIWORD(wParam))
			{//inicio sw3


			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTUSUARIOSELIMINAR, LB_GETCURSEL, NULL, NULL);
				usuarios* usuariosListaE = (usuarios*)SendDlgItemMessage(hDialogoActual, LBX_LISTUSUARIOSELIMINAR, LB_GETITEMDATA, indice, NULL);

				SetDlgItemTextA(hDialogoActual, LBL_USERNOMBELIMINAR, usuariosListaE->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_USERUSUARIOELIMINAR, usuariosListaE->user.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_USERPASSWORDELIMINAR, usuariosListaE->password.c_str());

				if (usuariosListaE->tipoUsuario == 1) {
					SetDlgItemTextA(hDialogoActual, LBL_USERTIPOELIMINAR, "admin");
				}
				else
				{
					SetDlgItemTextA(hDialogoActual, LBL_USERTIPOELIMINAR, "cajero");
				}

				SetDlgItemTextA(hDialogoActual, LBL_USERSUCURSALELIMINAR, usuariosListaE->sucursal.c_str());
				HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, usuariosListaE->RutaImagen, IMAGE_BITMAP, 128, 128, LR_LOADFROMFILE);
				HWND hPictureControl = GetDlgItem(hDialogoActual, PC_USUARIOSELIMINARIMG);
				SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);
			}
			break;

			}//fin sw3
		}
		break;

		}//fin sw2
	}
	break;

	}//fin sw
	return FALSE;
}
INT_PTR CALLBACK fnDlgUsuarioModificar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	int exitoUsuarioUs = 0;
	int exitoNombreUs = 0;
	int exitoSu = 0;
	string formato;
	string formatoS;
	int exitoPassLetra = 0;
	int exitoPassNum = 0;
	int exitoPassSpecial = 0;
	int contador = 1;

	switch (uMensaje)
	{//inicio sw

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_USUARIOSMODUS, auxUs->nombre.c_str());
	
		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_USUARIOMODIMG);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, TXT_MODNOMBRE, "");
		SetDlgItemTextA(hDialogoActual, TXT_MODUSER, "");
		SetDlgItemTextA(hDialogoActual, TXT_MODPASSWORD, "");
		SetDlgItemTextA(hDialogoActual, TXT_MODTIPO, "");
		SetDlgItemTextA(hDialogoActual, TXT_MODSUCURSAL, "");
		SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "");
		SetDlgItemTextA(hDialogoActual, LBL_USUARIOMODID, "");

		auxUsM = inicioListaUser;
		while (auxUsM != NULL)
		{
			string scontador = to_string(contador);
			formato = scontador + "- " + auxUsM->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTUSUARIOSMOD);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxUsM);
			auxUsM = auxUsM->sig;
			contador++;
		}

		//
		auxSu = inicioListaSucursal;
		while (auxSu != NULL)
		{
			string si = to_string(auxSu->id);
			formatoS = si + "-" + auxSu->nombre + " " + auxSu->direccion;
			HWND hListBoxS = GetDlgItem(hDialogoActual, LBX_MODUSERSUCURSAL);
			int indiceS = SendMessageA(hListBoxS, LB_ADDSTRING, 0, (LPARAM)formatoS.c_str());
			SendMessage(hListBoxS, LB_SETITEMDATA, indiceS, (LPARAM)auxSu);
			auxSu = auxSu->sig;

		}
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//inicio sw2

		case BTN_MODIFICARUSUARIO:
		{
			int ntipo;
			char cnombre[50], cuser[50], cpassword[50], csucursal[50], cid[3];

			GetDlgItemTextA(hDialogoActual, TXT_MODNOMBRE, cnombre, 50);
			string nombre(cnombre);
			GetDlgItemTextA(hDialogoActual, TXT_MODUSER, cuser, 50);
			string user(cuser);
			GetDlgItemTextA(hDialogoActual, TXT_MODPASSWORD, cpassword, 50);
			string password(cpassword);
			GetDlgItemTextA(hDialogoActual, TXT_MODSUCURSAL, csucursal, 50);
			string sucursal(csucursal);
			GetDlgItemTextA(hDialogoActual, LBL_USUARIOMODID, cid, 3);
			string sid(cid);
			int id = stoi(sid);

			auxSu = inicioListaSucursal;
			while (auxSu != NULL)
			{
				if (sucursal == auxSu->nombre)
				{
					exitoSu = 1;
					break;
				}

				auxSu = auxSu->sig;

			}

			for (int i = 0; i < password.size(); i++)
			{
				if ((password[i] >= 65 && password[i] <= 90) || (password[i] >= 97 && password[i] <= 122))
				{
					exitoPassLetra = 1;
				}
				if (password[i] >= 48 && password[i] <= 57)
				{
					exitoPassNum = 1;
				}
				if (password[i] >= 33 && password[i] <= 47)
				{
					exitoPassSpecial = 1;
				}
			}


			for (int i = 0; i < user.size(); i++)
			{
				if ((user[i] >= 65 && user[i] <= 90) || (user[i] >= 97 && user[i] <= 122) || user[i] >= 48 && user[i] <= 57)
				{
					exitoUsuarioUs = 1;
				}
				else
				{
					exitoUsuarioUs = 0;
					break;
				}
			}

			for (int i = 0; i < nombre.size(); i++)
			{
				if ((nombre[i] >= 65 && nombre[i] <= 90) || (nombre[i] >= 97 && nombre[i] <= 122) || nombre[i] == 32)
				{
					exitoNombreUs = 1;
				}
				else
				{
					exitoNombreUs = 0;
					break;
				}
			}


			if (nombre.empty() || user.empty() || password.empty() || sucursal.empty() || sid.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "Todos los campos son obligatorios");
			}

			else if (exitoSu != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "Debe elegir una sucursal de la lista");
			}

			else if (exitoUsuarioUs != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "El usuario solo puede tener letras y numeros");
			}

			else if (exitoNombreUs != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "El  nombre solo puede tener letras y espacios");
			}

			else if (exitoPassLetra != 1 && exitoPassNum && exitoPassSpecial != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "password min, 1 Letra, 1 Numero, 1 Special");
			}

			else if (password.size() < 3 || password.size() > 10)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "El Password debe ser minimo 3 caracteres y menos de 10");
			}

			else if (nombre.size() < 5 || nombre.size() > 50)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "El nombre deben ser minimo 5 caracteres y menos de 50");
			}

			else if (user.size() < 5 || user.size() > 20)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "El usuario deben ser minimo 5 caracteres y menos de 20");
			}

			else if (tipoUs < 0 && tipoUs > 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "Eliga un tipo de usuario");
			}

			else if (auxUs->id == id)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "No puede modificar el usuario actual");
			}

			else
			{

				auxUsM = inicioListaUser;
				while (auxUsM != NULL && auxUsM->id != id)
				{

					auxUsM = auxUsM->sig;
				}

				auxUsM->nombre = nombre;
				auxUsM->user = user;
				auxUsM->password = password;
				auxUsM->tipoUsuario = tipoUs;
				auxUsM->sucursal = sucursal;
				wstring ws = wstring(rutaImagenEnDisco);
				string imagen(ws.begin(), ws.end());
				strcpy_s(auxUsM->RutaImagen, imagen.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMODUSER, "Modificado correctamente");
			}
		}
		break;

		case LBX_LISTUSUARIOSMOD:
		{
			switch (HIWORD(wParam))
			{//inicio 3 switch

			case LBN_SELCHANGE:
			{

				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTUSUARIOSMOD, LB_GETCURSEL, NULL, NULL);
				usuarios* usuariosListaMod = (usuarios*)SendDlgItemMessage(hDialogoActual, LBX_LISTUSUARIOSMOD, LB_GETITEMDATA, indice, NULL);
				string idS = to_string(usuariosListaMod->id);
				SetDlgItemTextA(hDialogoActual, TXT_MODNOMBRE, usuariosListaMod->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, TXT_MODUSER, usuariosListaMod->user.c_str());
				SetDlgItemTextA(hDialogoActual, TXT_MODPASSWORD, usuariosListaMod->password.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_USUARIOMODID, idS.c_str());

				if (usuariosListaMod->tipoUsuario == 1)
				{
					SetDlgItemTextA(hDialogoActual, TXT_MODTIPO, "admin");
				}
				else
				{
					SetDlgItemTextA(hDialogoActual, TXT_MODTIPO, "cajero");
				}

				SetDlgItemTextA(hDialogoActual, TXT_MODSUCURSAL, usuariosListaMod->sucursal.c_str());

				HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, usuariosListaMod->RutaImagen, IMAGE_BITMAP, 128, 128, LR_LOADFROMFILE);
				HWND hPictureControl = GetDlgItem(hDialogoActual, PC_USUARIOSMODIMG);
				SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

			}
			break;

			}//fin 3 switch
		}
		break;

		case LBX_MODUSERSUCURSAL:
		{
			switch (HIWORD(wParam))
			{//Tercer Switch inicio
			case LBN_SELCHANGE:
			{
				int indiceS = SendDlgItemMessage(hDialogoActual, LBX_MODUSERSUCURSAL, LB_GETCURSEL, NULL, NULL);
				sucursales* sucursalListaM = (sucursales*)SendDlgItemMessage(hDialogoActual, LBX_MODUSERSUCURSAL, LB_GETITEMDATA, indiceS, NULL);

				SetDlgItemTextA(hDialogoActual, TXT_MODSUCURSAL, sucursalListaM->nombre.c_str());
			}
			break;

			}//Tercer Switch fin
		}
		break;

		case BTN_USUARIOSMODCARGARIMG:
		{
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			ofn.hwndOwner = hDialogoActual;
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFile = rutaImagenEnDisco;
			ofn.nMaxFile = 255;
			ofn.lpstrDefExt = L"Bmp";
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofn.lpstrFilter = L"Imagenes BMP\0* .bmp";

			if (GetOpenFileName(&ofn))
			{
				HBITMAP bitmap = (HBITMAP)LoadImage(hGlobalIdentificador, rutaImagenEnDisco, IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
				HWND hPictureControl = GetDlgItem(hDialogoActual, PC_USUARIOSMODIMG);
				SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "debe cargar una imagen");
			}
		}
		break;

		case RB_USUARIOSMODADMIN:
		{
			tipoUs = 1;
		}
		break;

		case RB_USUARIOSMODCAJERO:
		{
			tipoUs = 0;
		}
		break;

		case BTN_SALIRMODUSER:
		{

			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//fin sw2
	}
	break;

	}//fin sw

	return FALSE;
}
INT_PTR CALLBACK fnDlgUsuarioMostrar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	int contador = 1;
	string formato;
	switch (uMensaje)
	{//inicio switch
	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, IDC_STATIC1, auxUs->nombre.c_str());
	
		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_USUARIOMOSTRARIMGUS);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_MOSTRARNOMBRE, "");
		SetDlgItemTextA(hDialogoActual, LBL_MOSTRARUSER, "");
		SetDlgItemTextA(hDialogoActual, LBL_MOSTRARPASSWORD, "");
		SetDlgItemTextA(hDialogoActual, LBL_MOSTRARTIPO, "");
		SetDlgItemTextA(hDialogoActual, LBL_MOSTRARSUCURSAL, "");

		auxUsM = inicioListaUser;
		while (auxUsM != NULL)
		{
			string scontador = to_string(contador);
			formato = scontador + "- " + auxUsM->nombre;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTUSUARIOS);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxUsM);
			contador++;
			auxUsM = auxUsM->sig;

		}

	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//inicio 2 switch

		case LBX_LISTUSUARIOS:
		{
			switch (HIWORD(wParam))
			{//inicio 3 switch

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_LISTUSUARIOS, LB_GETCURSEL, NULL, NULL);
				usuarios* usuariosLista = (usuarios*)SendDlgItemMessage(hDialogoActual, LBX_LISTUSUARIOS, LB_GETITEMDATA, indice, NULL);

				SetDlgItemTextA(hDialogoActual, LBL_MOSTRARNOMBRE, usuariosLista->nombre.c_str());
				SetDlgItemTextA(hDialogoActual, LBL_MOSTRARUSER, usuariosLista->user.c_str());
				if (auxUs->tipoUsuario == 1)
				{
					SetDlgItemTextA(hDialogoActual, LBL_MOSTRARPASSWORD, usuariosLista->password.c_str());
				}
				else
				{
					SetDlgItemTextA(hDialogoActual, LBL_MOSTRARPASSWORD, "****");
				}

				if (usuariosLista->tipoUsuario == 1) {
					SetDlgItemTextA(hDialogoActual, LBL_MOSTRARTIPO, "Admin");
				}
				else
				{
					SetDlgItemTextA(hDialogoActual, LBL_MOSTRARTIPO, "cajero");
				}

				SetDlgItemTextA(hDialogoActual, LBL_MOSTRARSUCURSAL, usuariosLista->sucursal.c_str());

				HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, usuariosLista->RutaImagen, IMAGE_BITMAP, 128, 128, LR_LOADFROMFILE);
				HWND hPictureControl = GetDlgItem(hDialogoActual, PC_USUARIOSMOSIMG);
				SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);
				
			}
			break;

			}//fin 3 switch
		}
		break;

		case BTN_MOSTRARUSERSALIR:
		{

			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//fin 2 switch
	}
	break;

	}//Fin switch	

	return FALSE;
}
INT_PTR CALLBACK fnDlgUsuarioAgregar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	int imgCargada = 0;
	int exitoUsuarioUs = 0;
	int exitoNombreUs = 0;
	string formato;
	int i = 1;
	int exitoPassLetra = 0;
	int exitoPassNum = 0;
	int exitoPassSpecial = 0;

	switch (uMensaje)
	{//inicio switch

	case WM_INITDIALOG:
	{
	
		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_USUARIOAGREGARIMGUS);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		int id = 0;
		auxUsM = inicioListaUser;
		while (auxUsM != NULL)
		{
			auxUsM->id = id++;
			auxUsM = auxUsM->sig;
		}
		SetDlgItemTextA(hDialogoActual, LBL_NOMBREUSSESION, auxUs->nombre.c_str());
		SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "");
		auxSu = inicioListaSucursal;
		while (auxSu != NULL)
		{
			string si = to_string(i);
			formato = si + "-" + auxSu->nombre + " " + auxSu->direccion;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_USUARIOSSUCURSALES);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxSu);
			i++;
			auxSu = auxSu->sig;
		}

	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//inicio 2swit

		case LBX_USUARIOSSUCURSALES:
		{
			switch (HIWORD(wParam))
			{//Tercer Switch inicio
			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_USUARIOSSUCURSALES, LB_GETCURSEL, NULL, NULL);
				sucursales* sucursalLista = (sucursales*)SendDlgItemMessage(hDialogoActual, LBX_USUARIOSSUCURSALES, LB_GETITEMDATA, indice, NULL);

				SetDlgItemTextA(hDialogoActual, TXT_USUARIOSUCURSAL, sucursalLista->nombre.c_str());
			}
			break;

			}//Tercer Switch fin
		}
		break;


		case BTN_USUARIOAGREGAR:
		{

			int exitoSu = 0;
			char cnombre[50], cuser[50], cpassword[50], csucursal[50];

			GetDlgItemTextA(hDialogoActual, TXT_USUARIONOMBRE, cnombre, 50);
			string nombre(cnombre);
			GetDlgItemTextA(hDialogoActual, TXT_USUARIOUSER, cuser, 50);
			string user(cuser);
			GetDlgItemTextA(hDialogoActual, TXT_USUARIOPASSWORD, cpassword, 50);
			string password(cpassword);
			GetDlgItemTextA(hDialogoActual, TXT_USUARIOSUCURSAL, csucursal, 50);
			string sucursal(csucursal);

			//validaciones
			auxSu = inicioListaSucursal;
			while (auxSu != NULL)
			{
				if (sucursal == auxSu->nombre)
				{
					exitoSu = 1;
					break;
				}

				auxSu = auxSu->sig;

			}


			for (int i = 0; i < user.size(); i++)
			{
				if ((user[i] >= 65 && user[i] <= 90) || (user[i] >= 97 && user[i] <= 122) || user[i] >= 48 && user[i] <= 57)
				{
					exitoUsuarioUs = 1;
				}
				else
				{
					exitoUsuarioUs = 0;
					break;
				}
			}

			for (int i = 0; i < nombre.size(); i++)
			{
				if ((nombre[i] >= 65 && nombre[i] <= 90) || (nombre[i] >= 97 && nombre[i] <= 122) || nombre[i] == 32)
				{
					exitoNombreUs = 1;
				}
				else
				{
					exitoNombreUs = 0;
					break;
				}
			}

			for (int i = 0; i < password.size(); i++)
			{
				if ((password[i] >= 65 && password[i] <= 90) || (password[i] >= 97 && password[i] <= 122))
				{
					exitoPassLetra = 1;
				}
				if (password[i] >= 48 && password[i] <= 57)
				{
					exitoPassNum = 1;
				}
				if (password[i] >= 33 && password[i] <= 47)
				{
					exitoPassSpecial = 1;
				}
			}


			if (exitoPassLetra != 1 || exitoPassNum != 1 || exitoPassSpecial != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "El Password debe tener minimo 1 letra,  1 numero y 1 caracter special");
			}

			else if (exitoNombreUs == 0)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "El Nombre Solo pueden ser letras y espacios");
			}

			else if (exitoUsuarioUs == 0)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "El Usuario Solo pueden ser letras y numeros");
			}

			else if (password.size() < 3 || password.size() > 10)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "El Password debe ser minimo 3 caracteres y menos de 10");
			}

			else if (user.size() < 5 || user.size() > 20)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "El usuario deben ser minimo 5 caracteres y menos de 20");
			}
			else if (nombre.size() < 5 || nombre.size() > 50)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "El nombre deben ser minimo 5 caracteres y menos de 50");
			}
			else if (exitoSu != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "Debe escoger una sucursal de la la lista");
			}
			else if (nombre.empty() || user.empty() || password.empty()  || sucursal.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "Todos los campos son obligatorios");
			}
			else if (tipoUs < 0 && tipoUs > 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "Debe elegir un tipo de usuario");
			}
		

			else
			{

				agregarNodoUsuario(nombre, user, password, sucursal, tipoUs, rutaImagenEnDisco);
				SetDlgItemTextA(hDialogoActual, TXT_USUARIONOMBRE, "");
				SetDlgItemTextA(hDialogoActual, TXT_USUARIOUSER, "");
				SetDlgItemTextA(hDialogoActual, TXT_USUARIOPASSWORD, "");
				SetDlgItemTextA(hDialogoActual, TXT_USUARIOTIPO, "");
				SetDlgItemTextA(hDialogoActual, TXT_USUARIOSUCURSAL, "");
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "Usuario Agregado con Exito");
			}
		}
		break;

		case BTN_USUARIOAGREGARSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case BTN_USUARIOAGREGARCARGAR:
		{
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			ofn.hwndOwner = hDialogoActual;
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFile = rutaImagenEnDisco;
			ofn.nMaxFile = 255;
			ofn.lpstrDefExt = L"Bmp";
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofn.lpstrFilter = L"Imagenes BMP\0* .bmp";

			if (GetOpenFileName(&ofn))
			{
				HBITMAP bitmap = (HBITMAP) LoadImage(hGlobalIdentificador, rutaImagenEnDisco, IMAGE_BITMAP, 128, 128, LR_LOADFROMFILE);
				HWND hPictureControl = GetDlgItem(hDialogoActual, PC_USUARIOAGREGARIMAGEN);
				SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);
				
			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUSUARIOAGREGAR, "debe cargar una imagen");
			}
			imgCargada = 1;
		}
		break;

		case RB_USUARIOAGREGARADMIN:
		{
			tipoUs = 1;
		}
		break;

		case RB_USUARIOAGREGARCAJERO:
		{
			tipoUs = 0;
		}
		break;

		}//fin 2swit
	}
	break;

	}//fin switch

	return FALSE;
}
//usuarios ventanas

INT_PTR CALLBACK fnDlgReportePuntos(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	
	int contador = 1;
	int i = 0;
	string formato;

	switch (uMensaje)
	{//SW1

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_REPORTEPUNTOSNOMBRE, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_REPORTEPUNTOSIMGUS);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		cargandoArreglo();
		quicksort(arreglo, 0, cantidadClientes - 1);
		forCant = cantidadClientes;

		contador = cantidadClientes;
		
		for(int i = 0; i < cantidadClientes; i++)
		{
			string puntos = to_string(arreglo[i]->puntos);
			string scontador = to_string(contador);
			formato = scontador + " - " + arreglo[i]->nombre + ": " + puntos;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTUSUARIOS);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)arreglo[i]);
			contador--;
		}
	
		cantidadClientes = 0;

		
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//SW2

		case BTN_REPORTEPUNTOSCSV:
		{
			fstream archivo;
			archivo.open("Clientes Puntos.csv", ios::out);

			for (int i = forCant - 1; i >= 0; i--)
			{
				archivo << arreglo[i]->nombre << ","
					<< arreglo[i]->puntos << "\n";
			}

			archivo.close();
		}
		break;

		case BTN_REPORTEPUNTOSSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//SW2
	}
	break;

	}//SW1

	return FALSE;
}
INT_PTR CALLBACK fnDlgReportePromos(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	string formato;
	int contador = 1;
	switch (uMensaje)
	{//sw1

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_REPORTENOMBREUS, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_REPORTEPROMO);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		cargandoArregloPromo();
		quicksortPromos(arregloPromo, 0, cantidadPromos - 1);
		forPromo = cantidadPromos;

		contador = cantidadPromos;

		for (int i = 0; i < cantidadPromos; i++)
		{
			string canjeadas = to_string(arregloPromo[i]->canjeadasContador);
			string scontador = to_string(contador);
			formato = scontador + " - " + arregloPromo[i]->nombre + ": " + canjeadas;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTREPORTEPROMO);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)arregloPromo[i]);
			contador--;
		}

		cantidadPromos = 0;
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//sw2

		case BTN_REPORTEPROMOEXPORT:
		{
			fstream archivo;
			archivo.open("Promociones Canjeadas.csv", ios::out);

			for (int i = forPromo - 1; i >= 0; i--)
			{
				archivo << arregloPromo[i]->nombre << ","
					<< arregloPromo[i]->canjeadasContador << "\n";
			}

			archivo.close();
		}
		break;

		case BTN_REPORTEPROMOSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//sw2
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	}//sw1

	return FALSE;
}
INT_PTR CALLBACK fnDlgReporteDinero(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	int contador = 0;
	string formato;
	switch (uMensaje)
	{//sw1

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_REPORTEDINEROUS, auxUs->nombre.c_str());

		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_REPORTEDINERO);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		cargandoArreglo();
		quicksortDinero(arreglo, 0, cantidadClientes - 1);
		forCant = cantidadClientes;

		contador = cantidadClientes;

		for (int i = 0; i < cantidadClientes; i++)
		{
			string puntos = to_string(arreglo[i]->dineroGastado);
			string scontador = to_string(contador);
			formato = scontador + " - " + arreglo[i]->nombre + ": " + puntos;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_LISTREPORTEDINERO);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)arreglo[i]);
			contador--;
		}

		cantidadClientes = 0;
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//SW2

		case BTN_REPORTEDINEROEXPORT:
		{
			fstream archivo;
			archivo.open("Clientes Dinero.csv", ios::out);

			for (int i = forCant-1; i >= 0; i--)
			{
				archivo << arreglo[i]->nombre << ","
					<< arreglo[i]->dineroGastado << "\n";
			}

			archivo.close();
		}
		break;

		case BTN_REPORTEDINEROSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//SW2
	}
	break;

	}//sw1

	return FALSE;
}

//inicio
INT_PTR CALLBACK fnDlgMenu(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{

	switch (uMensaje)
	{//Primera Switch

	case WM_INITDIALOG:
	{
		HBITMAP bitmap = (HBITMAP)LoadImageA(hGlobalIdentificador, auxUs->RutaImagen, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
		HWND hPictureControl = GetDlgItem(hDialogoActual, PC_IMGMENU);
		SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

		SetDlgItemTextA(hDialogoActual, LBL_NOMBREMENU, auxUs->nombre.c_str());
		SetDlgItemTextA(hDialogoActual, LBL_USUARIOMENU, auxUs->user.c_str());
		SetDlgItemTextA(hDialogoActual, LBL_SUCURSALMENU, auxUs->sucursal.c_str());
		SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "");

		if (auxUs->tipoUsuario == 1)
		{
			SetDlgItemTextA(hDialogoActual, LBL_TIPOUSMENU, "Admin");
		}

		else if (auxUs->tipoUsuario == 0)
		{
			SetDlgItemTextA(hDialogoActual, LBL_TIPOUSMENU, "Cajero");
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//Segundo Switch

		case ID_USUARIOS_AGREGAR:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_USUARIOAGREGAR), NULL, fnDlgUsuarioAgregar);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
		}
		break;

		case ID_USUARIOS_MOSTRAR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_USUARIOMOSTRAR), NULL, fnDlgUsuarioMostrar);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
			SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "");
		}
		break;

		case ID_USUARIOS_MODIFICAR:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_USUARIOSMODIFICAR), NULL, fnDlgUsuarioModificar);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
		}
		break;

		case ID_USUARIOS_ELIMINAR:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_USUARIOELIMINAR), NULL, fnDlgUsuarioEliminar);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
		}
		break;

		case ID_SUCURSALES_AGREGAR:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_SUCURSALAGREGAR), NULL, fnDlgSucursalAgregar);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
		}
		break;

		case ID_SUCURSALES_MOSTRAR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_SUCURSALESMOSTRAR), NULL, fnDlgSucursalMostar);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
			SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "");


		}
		break;

		case ID_SUCURSALES_MODIFICAR:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_SUCURSALMODIFICAR), NULL, fnDlgSucursalModificar);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}

		}
		break;

		case ID_CLIENTES_AGREGAR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_CLIENTESAGREGAR), NULL, fnDlgClientesAgregar);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case ID_CLIENTES_MOSTRAR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_CLIENTESMOSTRAR), NULL, fnDlgClientesMostrar);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case ID_CLIENTES_MODIFICAR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_CLIENTESMODIFICAR), NULL, fnDlgClientesModificar);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case ID_CLIENTES_ELIMINARCLIENT:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_CLIENTESELIMINAR), NULL, fnDlgClientesEliminar);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}

			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
			
		}
		break;

		case ID_BRUNCHYPROMO_AGREGARR:
		{

			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_PROMOAGREGAR), NULL, fnDlgPromoAgregar);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
		}
		break;

		case ID_BRUNCHYPROMO_MOSTRAR40014:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_PROMOMOSTRAR), NULL, fnDlgPromoMostrar);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case ID_BRUNCHYPROMO_MODIFICAR40015:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_PROMOMODIFICAR), NULL, fnDlgPromoModificar);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
		}
		break;

		case ID_BRUNCHYPROMO_VENTA:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_PROMOPUNTOS), NULL, fnDlgPromoVenta);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case ID_BRUNCHYPROMO_ELIMINAR40016:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_PROMOELIMINAR), NULL, fnDlgPromoEliminar);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}

			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
			
		}
		break;

		case ID_SUCURSALES_ELIMINAR40022:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_SUCURSALESELIMINAR), NULL, fnDlgSucursalEliminar);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
			
		}
		break;

		case ID_REPORTES_PUNTAJECLIENTES:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_REPORTEPUNTAJECLIENTES), NULL, fnDlgReportePuntos);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}

			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
			
		}
		break;
		
		case ID_BRUNCHYPROMO_CANJEARPROMOCION:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_CANJEARELEGIRCLIENTE), NULL, fnDlgCanjear1);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case ID_REPORTES_BRUNCHYPROMOSCANJEADAS:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_REPORTEPROMO), NULL, fnDlgReportePromos);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}

			else 
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
			
		}
		break;

		case ID_REPORTES_VENTASTOTALESCLIENTES:
		{
			if (auxUs->tipoUsuario == 1)
			{
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_REPORTEDINERO), NULL, fnDlgReporteDinero);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}

			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORMENU, "Al ser cajero no puedes acceder a esa ventana");
			}
			
		}
		break;

		case BTN_SALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_INICIOSESION), NULL, fnDlgInicioSesion);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		}//Segundo Switch
	}
	break;


	}//Fin Switch

	return FALSE;
}
INT_PTR CALLBACK fnDlgInicioSesion(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	switch (uMensaje)
	{//Primer Switch

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_ERRORUS, "");
		SetDlgItemTextA(hDialogoActual, LBL_ERRORPASS, "");
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//SEGUNDO SWITCH
		case BTN_INICIOSESION:
		{
			char cuser[50], cpass[50];
			int exito = 0;

			GetDlgItemTextA(hDialogoActual, TXT_USUARIO, cuser, 50);
			GetDlgItemTextA(hDialogoActual, TXT_PASSWORD, cpass, 50);

			string user(cuser);
			string pass(cpass);

			auxUs = inicioListaUser;
			while (auxUs != NULL)
			{
				if (user == auxUs->user && pass == auxUs->password)
				{
					exito = 1;
					break;
				}
				auxUs = auxUs->sig;
			}

			if (exito == 1)
			{
				MessageBoxA(NULL, "Inicio Sesion Exitoso", "Inicio Sesion", MB_OK);
				HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_MENU), NULL, fnDlgMenu);
				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialogoActual);
			}

			else if (user.empty() && pass.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUS, "Todos los campos obligatorios");
				SetDlgItemTextA(hDialogoActual, LBL_ERRORPASS, "Todos los campos obligatorios");
			}

			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_ERRORUS, "Error en Credenciales");
				SetDlgItemTextA(hDialogoActual, LBL_ERRORPASS, "Error en Credenciales");
			}

		}
		break;

		case BTN_INICIOSESIONREGISTRAR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_REGISTRAR), NULL, fnDlgRegistrar);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case BTN_LIMPIAR:
		{
			PostQuitMessage(0);
		}
		break;

		}//FIN SEGUNDO SWITCH 
	}
	break;

	}//Fin Switch

	return FALSE;
}
INT_PTR CALLBACK fnDlgRegistrar(HWND hDialogoActual, UINT uMensaje, WPARAM wParam, LPARAM lParam)
{
	
	int imgCargada = 0;
	int exitoUsuarioUs = 0;
	int exitoNombreUs = 0;
	string formato;
	int i = 1;
	int exitoPassLetra = 0;
	int exitoPassNum = 0;
	int exitoPassSpecial = 0;

	switch (uMensaje)
	{

	case WM_INITDIALOG:
	{
		SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "");

		auxSu = inicioListaSucursal;
		while (auxSu != NULL)
		{
			string si = to_string(i);
			formato = si + "-" + auxSu->nombre + " " + auxSu->direccion;
			HWND hListBox = GetDlgItem(hDialogoActual, LBX_REGISTRARLISTSUCURSALES);
			int indice = SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)formato.c_str());
			SendMessage(hListBox, LB_SETITEMDATA, indice, (LPARAM)auxSu);
			i++;
			auxSu = auxSu->sig;
		}
	}
	break;

	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{//SW2
		

		case LBX_REGISTRARLISTSUCURSALES:
		{
			switch (HIWORD(wParam))
			{//SW3

			case LBN_SELCHANGE:
			{
				int indice = SendDlgItemMessage(hDialogoActual, LBX_REGISTRARLISTSUCURSALES, LB_GETCURSEL, NULL, NULL);
				sucursales* sucursalLista = (sucursales*)SendDlgItemMessage(hDialogoActual, LBX_REGISTRARLISTSUCURSALES, LB_GETITEMDATA, indice, NULL);

				SetDlgItemTextA(hDialogoActual, TXT_REGISTRARSUCURSAL, sucursalLista->nombre.c_str());
			}
			break;

			}//SW3
		
		}
		break;

		case BTN_REGISTRAR:
		{
			int exitoSu = 0;
			char cnombre[50], cuser[50], cpassword[50], csucursal[50];

			GetDlgItemTextA(hDialogoActual, TXT_REGISTRARNOMBRE, cnombre, 50);
			string nombre(cnombre);
			GetDlgItemTextA(hDialogoActual, TXT_REGISTRARUSER, cuser, 50);
			string user(cuser);
			GetDlgItemTextA(hDialogoActual, TXT_REGISTRARPASS, cpassword, 50);
			string password(cpassword);
			GetDlgItemTextA(hDialogoActual, TXT_REGISTRARSUCURSAL, csucursal, 50);
			string sucursal(csucursal);

			//validaciones
			auxSu = inicioListaSucursal;
			while (auxSu != NULL)
			{
				if (sucursal == auxSu->nombre)
				{
					exitoSu = 1;
					break;
				}

				auxSu = auxSu->sig;

			}


			for (int i = 0; i < user.size(); i++)
			{
				if ((user[i] >= 65 && user[i] <= 90) || (user[i] >= 97 && user[i] <= 122) || user[i] >= 48 && user[i] <= 57)
				{
					exitoUsuarioUs = 1;
				}
				else
				{
					exitoUsuarioUs = 0;
					break;
				}
			}

			for (int i = 0; i < nombre.size(); i++)
			{
				if ((nombre[i] >= 65 && nombre[i] <= 90) || (nombre[i] >= 97 && nombre[i] <= 122) || nombre[i] == 32)
				{
					exitoNombreUs = 1;
				}
				else
				{
					exitoNombreUs = 0;
					break;
				}
			}

			for (int i = 0; i < password.size(); i++)
			{
				if ((password[i] >= 65 && password[i] <= 90) || (password[i] >= 97 && password[i] <= 122))
				{
					exitoPassLetra = 1;
				}
				if (password[i] >= 48 && password[i] <= 57)
				{
					exitoPassNum = 1;
				}
				if (password[i] >= 33 && password[i] <= 47)
				{
					exitoPassSpecial = 1;
				}
			}


			if (exitoPassLetra != 1 || exitoPassNum != 1 || exitoPassSpecial != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "El Password debe tener minimo 1 letra,  1 numero y 1 caracter special");
			}

			else if (exitoNombreUs == 0)
			{
				SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "El Nombre Solo pueden ser letras y espacios");
			}

			else if (exitoUsuarioUs == 0)
			{
				SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "El Usuario Solo pueden ser letras y numeros");
			}

			else if (password.size() < 3 || password.size() > 10)
			{
				SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "El Password debe ser minimo 3 caracteres y menos de 10");
			}

			else if (user.size() < 5 || user.size() > 20)
			{
				SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "El usuario deben ser minimo 5 caracteres y menos de 20");
			}
			else if (nombre.size() < 5 || nombre.size() > 50)
			{
				SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "El nombre deben ser minimo 5 caracteres y menos de 50");
			}
			else if (exitoSu != 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "Debe escoger una sucursal de la la lista");
			}
			else if (nombre.empty() || user.empty() || password.empty() || sucursal.empty())
			{
				SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "Todos los campos son obligatorios");
			}
			else if (tipoUs < 0 && tipoUs > 1)
			{
				SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "Debe elegir un tipo de usuario");
			}

			else
			{
	
						agregarNodoUsuario(nombre, user, password, sucursal, tipoUs, rutaImagenEnDisco);
						SetDlgItemTextA(hDialogoActual, TXT_REGISTRARNOMBRE, "");
						SetDlgItemTextA(hDialogoActual, TXT_REGISTRARUSER, "");
						SetDlgItemTextA(hDialogoActual, TXT_REGISTRARPASS, "");
						SetDlgItemTextA(hDialogoActual, TXT_REGISTRARSUCURSAL, "");
						SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "Usuario Agregado con Exito");

				}
		}
		break;

		case RB_REGISTRARADMIN:
		{
			tipoUs = 1;
		}
		break;

		case RB_REGISTRARCAJERO:
		{
			tipoUs = 0;
		}
		break;

		case BTN_REGISTRARSALIR:
		{
			HWND  hDlg = CreateDialogW(hGlobalIdentificador, MAKEINTRESOURCE(DLG_INICIOSESION), NULL, fnDlgInicioSesion);
			ShowWindow(hDlg, SW_SHOW);
			DestroyWindow(hDialogoActual);
		}
		break;

		case BTN_REGISTRARCARGARIMG:
		{
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			ofn.hwndOwner = hDialogoActual;
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFile = rutaImagenEnDisco;
			ofn.nMaxFile = 255;
			ofn.lpstrDefExt = L"Bmp";
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofn.lpstrFilter = L"Imagenes BMP\0* .bmp";

			if (GetOpenFileName(&ofn))
			{
				HBITMAP bitmap = (HBITMAP)LoadImage(hGlobalIdentificador, rutaImagenEnDisco, IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
				HWND hPictureControl = GetDlgItem(hDialogoActual, PC_REGISTRARIMG);
				SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);
				imgCargada = 1;
			}
			else
			{
				SetDlgItemTextA(hDialogoActual, LBL_REGISTRARAVISO, "debe cargar una imagen");
			}
			imgCargada = 1;
		}
		break;

		}//SW2
	}
	break;

	}

	return FALSE;
}
//inicio

//fechahgbh
int getMonth()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	int month = 1 + newtime.tm_mon;
	return month;
}
int getYear()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	int year = 1900 + newtime.tm_year;
	return year;
}
int getDay()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	int day = newtime.tm_mday;
	return day;
}
//fecha
