package toDoList;


import org.springframework.data.repository.CrudRepository;

import javax.transaction.Transactional;
import java.util.List;

public interface listRepository extends CrudRepository<list, Long> {
    List<list> findAllByOwner(list owner);

    list findOneByIdAndOwner(Long id, list owner);

    @Transactional
    void deleteByIdAndOwner(Long id, list owner);
}