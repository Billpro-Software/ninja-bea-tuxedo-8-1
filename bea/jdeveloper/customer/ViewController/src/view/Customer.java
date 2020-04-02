package view;

import java.io.Serializable;

import java.sql.Timestamp;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;

@Entity
@NamedQueries({
  @NamedQuery(name = "Customer.findAll", query = "select o from Customer o")
})
public class Customer implements Serializable {
    @SuppressWarnings("compatibility:-1525070496950265806")
    private static final long serialVersionUID = -8445880043659720655L;
    @Column(name="CUST_ACCOUNT_TYPE", nullable = false, length = 4)
    private String custAccountType;
    @Column(name="CUST_ADDRESS_ID", length = 9)
    private String custAddressId;
    @Id
    @Column(name="CUST_CUSTOMER_ID", nullable = false)
    private Long custCustomerId;
    @Column(name="CUST_EMAIL", nullable = false, length = 100)
    private String custEmail;
    @Column(name="CUST_EMAIL_VERIFIED")
    private String custEmailVerified;
    @Column(name="CUST_NAME_ID", length = 9)
    private String custNameId;
    @Column(name="CUST_PASSWORD", nullable = false, length = 50)
    private String custPassword;
    @Column(name="CUST_PASS_LAST_CHG_DATE", nullable = false)
    private Timestamp custPassLastChgDate;

    public Customer() {
    }

    public Customer(String custAccountType, String custAddressId,
                    Long custCustomerId, String custEmail,
                    String custEmailVerified, String custNameId,
                    Timestamp custPassLastChgDate, String custPassword) {
        this.custAccountType = custAccountType;
        this.custAddressId = custAddressId;
        this.custCustomerId = custCustomerId;
        this.custEmail = custEmail;
        this.custEmailVerified = custEmailVerified;
        this.custNameId = custNameId;
        this.custPassLastChgDate = custPassLastChgDate;
        this.custPassword = custPassword;
    }

    public String getCustAccountType() {
        return custAccountType;
    }

    public void setCustAccountType(String custAccountType) {
        this.custAccountType = custAccountType;
    }

    public String getCustAddressId() {
        return custAddressId;
    }

    public void setCustAddressId(String custAddressId) {
        this.custAddressId = custAddressId;
    }

    public Long getCustCustomerId() {
        return custCustomerId;
    }

    public void setCustCustomerId(Long custCustomerId) {
        this.custCustomerId = custCustomerId;
    }

    public String getCustEmail() {
        return custEmail;
    }

    public void setCustEmail(String custEmail) {
        this.custEmail = custEmail;
    }

    public String getCustEmailVerified() {
        return custEmailVerified;
    }

    public void setCustEmailVerified(String custEmailVerified) {
        this.custEmailVerified = custEmailVerified;
    }

    public String getCustNameId() {
        return custNameId;
    }

    public void setCustNameId(String custNameId) {
        this.custNameId = custNameId;
    }

    public String getCustPassword() {
        return custPassword;
    }

    public void setCustPassword(String custPassword) {
        this.custPassword = custPassword;
    }

    public Timestamp getCustPassLastChgDate() {
        return custPassLastChgDate;
    }

    public void setCustPassLastChgDate(Timestamp custPassLastChgDate) {
        this.custPassLastChgDate = custPassLastChgDate;
    }
}
