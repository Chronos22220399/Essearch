#include <Arachne/NewSaver.h>
#include <sqlpp11/sqlite3/connection.h>

namespace Arachne {

NewSaver::NewSaver(std::shared_ptr<sqlpp::sqlite3::connection_pool> pool)
    : pool(pool) {
  if (pool == nullptr) {
    LOG("{}", "连接池未初始化 -- NewSaver");
    exit(-1);
  }
}

NewSaver::SaveStatus NewSaver::save_new(const NewParser::New &n,
                                        bool can_update) {
  auto conn_ptr = std::make_shared<
      sqlpp::pooled_connection<sqlpp::sqlite3::connection_base>>(pool->get());

  LOG("{}", "pool 可获取");
  if (conn_ptr->is_connected()) {
    // 确保所有字段都有正确的赋值
    try {
      News::New nw{};
      Autils::ScopedTranscation trans(conn_ptr);

      auto not_exists =
          (*conn_ptr)(select(nw.title).from(nw).where(nw.title == n.title))
              .empty();

      if (not_exists) {
        // TODO:
        // 给 Hepheastus 构建倒排索引

        (*conn_ptr)(insert_into(nw).set(
            nw.title = n.title, nw.authorPhotor = n.authorPhotor,
            nw.referring = n.referring, nw.source = n.source,
            nw.clickedCnt = n.clickedCnt, nw.content = n.content,
            nw.editor = n.editor, nw.url = n.url));
        trans.commit();
        return SaveStatus::SaveSuccess;
      } else if (can_update) {
        LOG("{}", "新闻已存在，更新");
        (*conn_ptr)(update(nw)
                        .set(nw.authorPhotor = n.authorPhotor,
                             nw.referring = n.referring, nw.source = n.source,
                             nw.clickedCnt = n.clickedCnt,
                             nw.content = n.content, nw.editor = n.editor,
                             nw.url = n.url)
                        .where(nw.title == n.title));
        trans.commit();
        return SaveStatus::UpdateSuccess;
      } else {
        LOG("{}", "新闻已存在，不更新");
        // TODO:
        // 返回已存在,不更新的信息
        trans.commit();
        return SaveStatus::DoNoThing;
      }
      // 未执行到此处会自动回滚
    } catch (const sqlpp::exception &e) {
      LOG("数据库错误: {}", e.what());
      return SaveStatus::DBError;
    } catch (const std::exception &e) {
      LOG("系统错误: {}", e.what());
      return SaveStatus::SysError;
    }
  } else {
    LOG("无法连接");
    return SaveStatus::CannotConn;
  }
  return SaveStatus::DoNoThing;
}

} // namespace Arachne
