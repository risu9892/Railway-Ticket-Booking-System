// g++ executor.cpp -o executor && ./executor
#include "components.cpp"
#define deb(x) cout << #x << " " << x << endl;
/*

    our final user experiance will be:

        1. we will display station code with station name

        2. user will give starting and ending journey stations
        3. user will give journy date(one of next five days)
        
        4. we will display trains no + train name + avalibility

        5. user will give train number
        6. user will give no of passenger
            6.1 user will give one by one detail(name+age+gender) of every passenger

        7. user will enter transition id

        8. we will give alloted seat numbers
        

*/



int main(){

    system("CLS");

    int from, to;
    char jdate[15];
    int selected_train, passengers;
    int RorC;

    cout << "\n\n\t\t\t\tWelcome to Railway Ticket Booking System" << endl;
    
    cout << "\n\tPlease Press: \n\t\t1. for Reservation\n\t\t0. to exit" << endl;
    cout << "\t\t\t"; 
    cin >> RorC;
        
    load_data();
    
    
    

    do{

        re_read();
        ticket sudo_tkt;
    
        if(RorC == 1){
            system("CLS");        
            cout << "\tStations:" << endl << "\t\tStation code    Station name" << endl;     
            for(int i = 0; i < 16; i++){
            cout << "\t\t" << STATIONS.Stations[i].st_no << ".\t\t" << STATIONS.Stations[i].st_name << endl;
            }

            cout << "Enter journy starting station code" << endl;
            cin >> TICKETS.tickets[TICKETS.ticket_counter].from;
            
            cout << "Enter end station code" << endl;
            cin >> TICKETS.tickets[TICKETS.ticket_counter].to;
            
            cout << "Enter journy date(in dd/mm/yyyy format)    " << endl;
            cin >> TICKETS.tickets[TICKETS.ticket_counter].jdate;
            
            if(TICKETS.tickets[TICKETS.ticket_counter].from == TICKETS.tickets[TICKETS.ticket_counter].to){
                cout << "starting and end station cann't be same" << endl;
                continue;
            }

            else if(TICKETS.tickets[TICKETS.ticket_counter].from < TICKETS.tickets[TICKETS.ticket_counter].to){
                // upgoing delhi to patna
                TICKETS.tickets[TICKETS.ticket_counter].tr_start_DorP = 'd';
            
                bool isAny = false;
                system("CLS");
                cout << "train list for delhi to patna" << endl;
                vector<pair<deque<int>, int>> dp; 
                int train_counter = 0;               
                for(int i = 0; i < 10; i++){
                    if(!strcmp(TRAINS.DtoP[i].jdate, TICKETS.tickets[TICKETS.ticket_counter].jdate)){
                        cout << TRAINS.DtoP[i].train_number << "\t" << TRAINS.DtoP[i].train_name << " ";
                        pair<deque<int>, int> temp = available_seats(TICKETS.tickets[TICKETS.ticket_counter], i);
                        if(temp.second > 0){ 
                            cout << "Available seats: " <<  temp.second  << endl;
                            isAny = true;
                            dp.push_back(make_pair(temp.first, TRAINS.DtoP[i].train_number));
                            train_counter++;
                        }
                        else{
                            cout << "NO SEAT AVAILABLE" << endl;
                        } 
                    }
                } 
                
                if(isAny){
                
                    cout << "Enter train number" << endl;
                    cin >> TICKETS.tickets[TICKETS.ticket_counter].train_no;

                    system("CLS");

                    cout << "Enter no. of passengers" << endl;
                    cin >> TICKETS.tickets[TICKETS.ticket_counter].psgr_count;

                    
                
                    cout << "Enter detail of passenger (name, gender[M/F], age)" << endl;
                    for(int i = 0; i < TICKETS.tickets[TICKETS.ticket_counter].psgr_count; i++){

                        cin >> TICKETS.tickets[TICKETS.ticket_counter].psgrs[i].name;
                        cin >> TICKETS.tickets[TICKETS.ticket_counter].psgrs[i].gender;
                        cin >> TICKETS.tickets[TICKETS.ticket_counter].psgrs[i].age;
                        if(i + 1 != TICKETS.tickets[TICKETS.ticket_counter].psgr_count) cout << "enter next passenger's detail" << endl;

                    }
                    
                    int tcno;
                    for(int i = 0; i < train_counter; i++){ 
                        
                        if( dp[i].second == TICKETS.tickets[TICKETS.ticket_counter].train_no){
                            tcno = book_ticket(dp[i].first);
                            deb(tcno);
                            break;
                        }
                        cout << endl;
                    }

                    system("CLS");                    
                    
                    string transation_id;
                    cout << "total ammount: " << TICKETS.tickets[tcno].amount << endl ;
                    cout << "Enter transaction id" << endl;
                    cin >> transation_id;
                    if(transation_id == "12345"){
                        system("CLS");    
                        cout << "\n\t\t\t\t\tReservation Succesfull\n" << endl;
                        cout << "\t\t\tPNR number : " << TICKETS.tickets[tcno].pnr << endl;
                        cout << "\t\t\tTrain Number:" << TICKETS.tickets[tcno].train_no << endl;
                        cout << "\t\t\tStarting Station:" << TICKETS.tickets[tcno].from << endl;
                        cout << "\t\t\tEnd Station:" << TICKETS.tickets[tcno].to << endl;
                        cout << "\t\t\tJourney Date:" << TICKETS.tickets[tcno].jdate << endl;
                        cout << "\t\t\tNo of Passengers:" << TICKETS.tickets[tcno].psgr_count << endl;
                        cout << "\t\t\talloted seats: \n";
                        for(int i = 0; i < TICKETS.tickets[tcno].psgr_count; i++) cout << "\t\t\t\t" << i+1 << ". " << TICKETS.tickets[tcno].psgrs[i].name << "\t" << TICKETS.tickets[tcno].psgrs[i].seat << " \n";    cout << endl;
                        cout << endl;
                        for(int i = 0; i < 130; i++) cout << "_"; cout << endl;
                    }
                    else{
                        cout << "incorrect transation id\n" << endl; 
                    }
                }
                else{
                    cout << "No seat available on " << jdate << " please try on another date" << endl;
                }
            }
            else{
            
               // upgoing patna to delhi
                TICKETS.tickets[TICKETS.ticket_counter].tr_start_DorP = 'p';
            
                bool isAny = false;
                system("CLS");
                cout << "train list for patna to delhi" << endl;
                vector<pair<deque<int>, int>> dp; 
                int train_counter = 0;               
                for(int i = 0; i < 10; i++){
                    if(!strcmp(TRAINS.PtoD[i].jdate, TICKETS.tickets[TICKETS.ticket_counter].jdate)){
                        cout << TRAINS.PtoD[i].train_number << "\t" << TRAINS.DtoP[i].train_name << " ";
                        pair<deque<int>, int> temp = available_seats(TICKETS.tickets[TICKETS.ticket_counter], i);
                        if(temp.second > 0){ 
                            cout << "Available seats: " <<  temp.second  << endl;
                            isAny = true;
                            dp.push_back(make_pair(temp.first, TRAINS.DtoP[i].train_number));
                            train_counter++;
                        }
                        else{
                            cout << "NO SEAT AVAILABLE" << endl;
                        } 
                    }
                } 
                
                if(isAny){
                
                    cout << "Enter train number" << endl;
                    cin >> TICKETS.tickets[TICKETS.ticket_counter].train_no;

                    system("CLS");

                    cout << "Enter no. of passengers" << endl;
                    cin >> TICKETS.tickets[TICKETS.ticket_counter].psgr_count;

                    
                
                    cout << "Enter detail of passenger (name, gender[M/F], age)" << endl;
                    for(int i = 0; i < TICKETS.tickets[TICKETS.ticket_counter].psgr_count; i++){

                        cin >> TICKETS.tickets[TICKETS.ticket_counter].psgrs[i].name;
                        cin >> TICKETS.tickets[TICKETS.ticket_counter].psgrs[i].gender;
                        cin >> TICKETS.tickets[TICKETS.ticket_counter].psgrs[i].age;
                        if(i + 1 != TICKETS.tickets[TICKETS.ticket_counter].psgr_count) cout << "enter next passenger's detail" << endl;

                    }
                    
                    int tcno;
                    for(int i = 0; i < train_counter; i++){ 
                        
                        if( dp[i].second == TICKETS.tickets[TICKETS.ticket_counter].train_no){
                            tcno = book_ticket(dp[i].first);
                            deb(tcno);
                            break;
                        }
                        cout << endl;
                    }

                    system("CLS");                    
                    
                    string transation_id;
                    cout << "total ammount: " << TICKETS.tickets[tcno].amount << endl ;
                    cout << "Enter transaction id" << endl;
                    cin >> transation_id;
                    if(transation_id == "12345"){
                        system("CLS");    
                        cout << "\n\t\t\t\t\tReservation Succesfull\n" << endl;
                        cout << "\t\t\tPNR number : " << TICKETS.tickets[tcno].pnr << endl;
                        cout << "\t\t\tTrain Number:" << TICKETS.tickets[tcno].train_no << endl;
                        cout << "\t\t\tStarting Station:" << TICKETS.tickets[tcno].from << endl;
                        cout << "\t\t\tEnd Station:" << TICKETS.tickets[tcno].to << endl;
                        cout << "\t\t\tJourney Date:" << TICKETS.tickets[tcno].jdate << endl;
                        cout << "\t\t\tNo of Passengers:" << TICKETS.tickets[tcno].psgr_count << endl;
                        cout << "\t\t\talloted seats: \n";
                        for(int i = 0; i < TICKETS.tickets[tcno].psgr_count; i++) cout << "\t\t\t\t" << i+1 << ". " << TICKETS.tickets[tcno].psgrs[i].name << "\t" << TICKETS.tickets[tcno].psgrs[i].seat << " \n";    cout << endl;
                        cout << endl;
                        for(int i = 0; i < 130; i++) cout << "_"; cout << endl;
                    }
                    else{
                        cout << "incorrect transation id\n" << endl; 
                    }
                }
                else{
                    cout << "No seat available on " << jdate << " please try on another date" << endl;
                }

            }

            re_write();
        }

        // system("CLS");
        cout << "\n\tPlease Press: \n\t\t1. for Reservation\n\t\t0. to exit" << endl;
        cin >> RorC;
        // system("CLS");

    }while(RorC != 0);
}
