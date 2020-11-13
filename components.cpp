// g++ test.cpp -o test && ./test

#include "components.cpp"


int book(deque<int> avl_seats){

    int tno = TICKETS.ticket_counter;
    ticket tkt = TICKETS.tickets[tno];
    int trid = tkt.train_no/13 - 1369;
    int alloted_seat;

    tkt.amount = (STATIONS.Stations[tkt.from].km - STATIONS.Stations[tkt.to].km)*13;

    if(tkt.tr_start_DorP == 'd'){

        for(int i = 0; i < tkt.psgr_count; i++){
            if(tkt.psgrs[i].age >= 60 || tkt.psgrs[i].gender == 'f' || tkt.psgrs[i].gender == 'F'){
                alloted_seat = avl_seats.front();
                avl_seats.pop_front();
            }
            else{
                alloted_seat = avl_seats.back();
                avl_seats.pop_back();
            }
            markD(tkt.from, tkt.to, trid, alloted_seat);
        }

    }
    else{
        
        for(int i = 0; i < tkt.psgr_count; i++){
            if(tkt.psgrs[i].age >= 60 || tkt.psgrs[i].gender == 'f' || tkt.psgrs[i].gender == 'F'){
                alloted_seat = avl_seats.front();
                avl_seats.pop_front();
            }
            else{
                alloted_seat = avl_seats.back();
                avl_seats.pop_back();
            }
            markP(tkt.from, tkt.to, trid, alloted_seat);
        }

    }
    
    TICKETS.tickets[tno] = tkt;
    return TICKETS.ticket_counter++;
}

int main(){

    load_data();
    


}
