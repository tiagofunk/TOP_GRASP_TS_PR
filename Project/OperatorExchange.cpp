#include "OperatorExchange.h"
#include "main.h"

Solution * OperatorExchange::realize_operation( Solution * sol ){
    this->is_swaped = false;
    Solution * actual = new Solution( *sol );
    Solution * best   = new Solution( *sol );
    for( int i = 0; i < actual->get_number_paths(); i++ ){
        for( int j = i+1; j < actual->get_number_paths(); j++ ){
            for( int k = 1; k < actual->get_length_of_path( i )-1; k++ ){
                for( int l = 1; l < actual->get_length_of_path( j )-1; l++ ){
                    actual->swap( i, k, j, l );
                    if( actual->get_total_time() < best->get_total_time() ){
                        delete best;
                        best = new Solution( *actual );
                        this->is_swaped = true;
                    }
                    delete actual;
                    actual = new Solution( *sol );
                }
            }
        }
    }
    delete sol;
    return best;
}

Solution * OperatorExchange::execute( Solution * s, vector< Vertice * > unused_vertices ){
    this->unused_vertices = unused_vertices;
    int count = 0;
    do{
        s = this->realize_operation( s );
        count++;
    }while( this->is_swaped );
    show_log( "number of exchanges: " + std::to_string( count ) + "\n", 3 );
    return s;
}